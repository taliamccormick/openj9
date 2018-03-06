/*******************************************************************************
 * Copyright (c) 2001, 2018 IBM Corp. and others
 *
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License 2.0 which accompanies this
 * distribution and is available at https://www.eclipse.org/legal/epl-2.0/
 * or the Apache License, Version 2.0 which accompanies this distribution and
 * is available at https://www.apache.org/licenses/LICENSE-2.0.
 *
 * This Source Code may also be made available under the following
 * Secondary Licenses when the conditions for such availability set
 * forth in the Eclipse Public License, v. 2.0 are satisfied: GNU
 * General Public License, version 2 with the GNU Classpath
 * Exception [1] and GNU General Public License, version 2 with the
 * OpenJDK Assembly Exception [2].
 *
 * [1] https://www.gnu.org/software/classpath/license.html
 * [2] http://openjdk.java.net/legal/assembly-exception.html
 *
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0 WITH Classpath-exception-2.0 OR LicenseRef-GPL-2.0 WITH Assembly-exception
 *******************************************************************************/
#include "j2sever.h"
#include "j9.h"
#include "j9cp.h"
#include "../util/ut_module.h"
#undef UT_MODULE_LOADED
#undef UT_MODULE_UNLOADED
#include "ut_j9vm.h"
#include "util_api.h"
#include "vm_internal.h"
#include "j9protos.h"

#if defined(J9VM_OPT_VALHALLA_NESTMATES)
static UDATA loadAndVerifyNestHost(J9VMThread *vmThread, J9Class *clazz);
#endif /* defined(J9VM_OPT_VALHALLA_NESTMATES) */

/**
 * Check visibility from sourceClass to destClass with modifiers specified
 *
 * @param[in] currentThread the current J9VMThread
 * @param[in] sourceClass the accessing class
 * @param[in] destClass: the accessed class
 * @param[in] modifiers the modifier
 * @param[in] lookupOptions J9_LOOK* options
 *
 * @return 	J9_VISIBILITY_ALLOWED if the access is allowed,
 * 			J9_VISIBILITY_NON_MODULE_ACCESS_ERROR if the access is NOT allowed due to non-module access error,
 * 			J9_VISIBILITY_MODULE_READ_ACCESS_ERROR if module read access error occurred,
 * 			J9_VISIBILITY_MODULE_PACKAGE_EXPORT_ERROR if module package access error
 */
IDATA
checkVisibility(J9VMThread *currentThread, J9Class* sourceClass, J9Class* destClass, UDATA modifiers, UDATA lookupOptions)
{
	UDATA result = J9_VISIBILITY_ALLOWED;
	J9JavaVM * const vm = currentThread->javaVM;
	
	Trc_VM_checkVisibility_Entry(currentThread, sourceClass, destClass, modifiers);
	sourceClass = J9_CURRENT_CLASS(sourceClass);
	destClass = J9_CURRENT_CLASS(destClass);
#ifdef DEBUG
	printf("checkModVis: [%*s] [%*s]\n",
				J9UTF8_LENGTH(J9ROMCLASS_CLASSNAME(sourceClass->romClass)), J9UTF8_DATA(J9ROMCLASS_CLASSNAME(sourceClass->romClass)),
				J9UTF8_LENGTH(J9ROMCLASS_CLASSNAME(destClass->romClass)), J9UTF8_DATA(J9ROMCLASS_CLASSNAME(destClass->romClass)));
#endif
	if (J9ROMCLASS_IS_UNSAFE(sourceClass->romClass) == 0) {
		if ( modifiers & J9AccPublic ) {
			/* Public */
			if ((sourceClass != destClass) 
				&& (J2SE_VERSION(vm) >= J2SE_19) 
				&& J9_ARE_ALL_BITS_SET(vm->runtimeFlags, J9_RUNTIME_JAVA_BASE_MODULE_CREATED)
				&& !J9ROMCLASS_IS_PRIMITIVE_TYPE(destClass->romClass)
			) {
				J9Module *srcModule = sourceClass->module;
				J9Module *destModule = destClass->module;
				if (srcModule != destModule) {
					UDATA rc = ERRCODE_GENERAL_FAILURE;
					if (!J9_ARE_ALL_BITS_SET(lookupOptions, J9_LOOK_REFLECT_CALL)) {
						if (!isAllowedReadAccessToModule(currentThread, srcModule, destModule, &rc)) {
							Trc_VM_checkVisibility_failed_with_errortype(currentThread,
									sourceClass, J9UTF8_LENGTH(J9ROMCLASS_CLASSNAME(sourceClass->romClass)), J9UTF8_DATA(J9ROMCLASS_CLASSNAME(sourceClass->romClass)),
									destClass, J9UTF8_LENGTH(J9ROMCLASS_CLASSNAME(destClass->romClass)), J9UTF8_DATA(J9ROMCLASS_CLASSNAME(destClass->romClass)), "read access not allowed");
							result = J9_VISIBILITY_MODULE_READ_ACCESS_ERROR;
						}
					}

					if (J9_VISIBILITY_ALLOWED == result) {
						const U_8* packageName = NULL;
						UDATA packageNameLength = 0;
						J9PackageIDTableEntry entry = {0};

						entry.taggedROMClass = destClass->packageID;
						packageName = getPackageName(&entry, &packageNameLength);

						omrthread_monitor_enter(vm->classLoaderModuleAndLocationMutex);
						if (!isPackageExportedToModuleWithName(currentThread, destModule, (U_8*) packageName, (U_16) packageNameLength, srcModule, J9_IS_J9MODULE_UNNAMED(vm, srcModule), &rc)) {
							Trc_VM_checkVisibility_failed_with_errortype(currentThread,
									sourceClass, J9UTF8_LENGTH(J9ROMCLASS_CLASSNAME(sourceClass->romClass)), J9UTF8_DATA(J9ROMCLASS_CLASSNAME(sourceClass->romClass)),
									destClass, J9UTF8_LENGTH(J9ROMCLASS_CLASSNAME(destClass->romClass)), J9UTF8_DATA(J9ROMCLASS_CLASSNAME(destClass->romClass)), "package not exported");
							result = J9_VISIBILITY_MODULE_PACKAGE_EXPORT_ERROR;
						}
						omrthread_monitor_exit(vm->classLoaderModuleAndLocationMutex);
					}

				}
			}
		} else if (modifiers & J9AccPrivate) {
			/* Private */
			if (sourceClass != destClass) {
#if defined(J9VM_OPT_VALHALLA_NESTMATES)
				/* loadAndVerifyNestHost returns an error if setting nest host field fails */
				if (NULL == destClass->nestHost) {
					result = loadAndVerifyNestHost(currentThread, destClass);
				}
				if ((J9_VISIBILITY_ALLOWED == result) && (NULL == sourceClass->nestHost)) {
					result = loadAndVerifyNestHost(currentThread, sourceClass);
				}
				if ((J9_VISIBILITY_ALLOWED == result) && (sourceClass->nestHost != destClass->nestHost)) {
#endif /* defined(J9VM_OPT_VALHALLA_NESTMATES) */
					result = J9_VISIBILITY_NON_MODULE_ACCESS_ERROR;
#if defined(J9VM_OPT_VALHALLA_NESTMATES)
				}
#endif /* defined(J9VM_OPT_VALHALLA_NESTMATES) */
			}
		} else if (modifiers & J9AccProtected) {
			/* Protected */
			if (sourceClass->packageID != destClass->packageID) {
				if (J9_ARE_ANY_BITS_SET(sourceClass->romClass->modifiers, J9AccInterface)) {
					/* Interfaces are types, not classes, and do not have protected access to 
					 * their 'superclass' (java.lang.Object) 
					 */
					result = J9_VISIBILITY_NON_MODULE_ACCESS_ERROR;
				} else {
					/* not same package so sourceClass must be a subclass of destClass */
					if (!isSameOrSuperClassOf(destClass, sourceClass)) {
						result = J9_VISIBILITY_NON_MODULE_ACCESS_ERROR;
					}
				}
			}
		} else {
			/* Default (package access) */
			if (sourceClass->packageID != destClass->packageID) {
				result = J9_VISIBILITY_NON_MODULE_ACCESS_ERROR;
			}
		}
	}

	if (J9_VISIBILITY_NON_MODULE_ACCESS_ERROR == result) {
		/* "checkVisibility from %p (%.*s) to %p (%.*s) modifiers=%zx failed" */
		Trc_VM_checkVisibility_Failed(currentThread,
			sourceClass, J9UTF8_LENGTH(J9ROMCLASS_CLASSNAME(sourceClass->romClass)), J9UTF8_DATA(J9ROMCLASS_CLASSNAME(sourceClass->romClass)),
			destClass, J9UTF8_LENGTH(J9ROMCLASS_CLASSNAME(destClass->romClass)), J9UTF8_DATA(J9ROMCLASS_CLASSNAME(destClass->romClass)),
			modifiers);
	}

	Trc_VM_checkVisibility_Exit(currentThread, result);

	return result;
}

#if defined(J9VM_OPT_VALHALLA_NESTMATES)
static UDATA loadAndVerifyNestHost(J9VMThread *vmThread, J9Class *clazz) {
	J9Class *nestHost = NULL;
	UDATA result = J9_VISIBILITY_ALLOWED;
	J9ROMClass *romClass = clazz->romClass;
	J9UTF8 *nestHostName = J9ROMCLASS_NESTHOSTNAME(romClass);

	/* If no nest host is named, class is own nest host */
	if (NULL == nestHostName) {
		nestHost = clazz;
	} else {
		UDATA classLoadingFlags = J9_FINDCLASS_FLAG_THROW_ON_FAIL;
		nestHost = internalFindClassUTF8(vmThread, J9UTF8_DATA(nestHostName), J9UTF8_LENGTH(nestHostName), clazz->classLoader, classLoadingFlags);

		/* Nest host must be successfully loaded by the same classloader in the same package & verify the nest member */
		if (NULL == nestHost) {
			result = J9_VISIBILITY_NEST_HOST_LOADING_FAILURE_ERROR;
		} else if (clazz->packageID != nestHost->packageID) {
			result = J9_VISIBILITY_NEST_HOST_DIFFERENT_PACKAGE_ERROR;
		} else {
			/* The nest host must have a nestmembers attribute that claims this class. */
			BOOLEAN verified = FALSE;
			J9UTF8 *className = J9ROMCLASS_CLASSNAME(romClass);
			J9SRP *nestMembers = J9ROMCLASS_NESTMEMBERS(nestHost->romClass);
			U_16 nestMemberCount = nestHost->romClass->nestMemberCount;
			U_16 i = 0;

			for (i = 0; i < nestMemberCount; i++) {
				J9UTF8 *nestMemberName = NNSRP_GET(nestMembers[i], J9UTF8*);
				if (J9UTF8_EQUALS(className, nestMemberName)) {
					verified = TRUE;
					break;
				}
			}
			if (!verified) {
				result = J9_VISIBILITY_NEST_MEMBER_NOT_CLAIMED_ERROR;
			}
		}
	}

	/* If a problem occurred in nest host verification then the nest host value is invalid */
	if  ((J9_VISIBILITY_ALLOWED == result) && (nestHost != NULL)) {
		clazz->nestHost = nestHost;
	}
	return result;
}
#endif /* defined(J9VM_OPT_VALHALLA_NESTMATES) */
