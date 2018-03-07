/*******************************************************************************
 * Copyright (c) 2018, 2018 IBM Corp. and others
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

package com.ibm.jvmti.tests.nestMatesRedefinition;

import org.objectweb.asm.*;
import org.objectweb.asm.ClassWriter;
import org.objectweb.asm.FieldVisitor;
import org.objectweb.asm.MethodVisitor;
import org.objectweb.asm.Opcodes;


public class ClassGenerator implements Opcodes {

	public static byte[] nestHostNoAttribute () throws Exception {
		ClassWriter classWriter = new ClassWriter(0);

		classWriter.visit(V1_8, ACC_PUBLIC | ACC_SUPER, "NestHost", null, "java/lang/Object", null);
		classWriter.visitSource("NestHost.java", null);		

		MethodVisitor methodVisitor;
		methodVisitor = classWriter.visitMethod(ACC_PUBLIC, "<init>", "()V", null, null);
		methodVisitor.visitCode();
		Label label0 = new Label();
		methodVisitor.visitLabel(label0);
		methodVisitor.visitLineNumber(2, label0);
		methodVisitor.visitVarInsn(ALOAD, 0);
		methodVisitor.visitMethodInsn(INVOKESPECIAL, "java/lang/Object", "<init>", "()V", false);
		methodVisitor.visitInsn(RETURN);
		methodVisitor.visitMaxs(1, 1);
		methodVisitor.visitEnd();

		classWriter.visitEnd();
		return classWriter.toByteArray();
	}

	public static byte[] nestHostWithNestMembersAttribute () throws Exception {
		ClassWriter classWriter = new ClassWriter(0);

		classWriter.visit(V1_8, ACC_PUBLIC | ACC_SUPER, "NestHost", null, "java/lang/Object", null);
		classWriter.visitSource("NestHost.java", null);

		MethodVisitor methodVisitor;
		methodVisitor = classWriter.visitMethod(ACC_PUBLIC, "<init>", "()V", null, null);
		methodVisitor.visitCode();
		Label label0 = new Label();
		methodVisitor.visitLabel(label0);
		methodVisitor.visitLineNumber(2, label0);
		methodVisitor.visitVarInsn(ALOAD, 0);
		methodVisitor.visitMethodInsn(INVOKESPECIAL, "java/lang/Object", "<init>", "()V", false);
		methodVisitor.visitInsn(RETURN);
		methodVisitor.visitMaxs(1, 1);
		methodVisitor.visitEnd();

		String[] nestMembers = {"A", "B", "C"};
		NestMembersAttribute attr = new NestMembersAttribute(nestmems);
		classWriter.visitAttribute(attr);

		classWriter.visitEnd();
		return classWriter.toByteArray();
	}

	public static byte[] nestMemberNoAttribute () throws Exception {
		ClassWriter classWriter = new ClassWriter(0);

		classWriter.visit(V1_8, ACC_PUBLIC | ACC_SUPER, "NestMembers", null, "java/lang/Object", null);
		classWriter.visitSource("NestHost.java", null);		

		MethodVisitor methodVisitor;
		methodVisitor = classWriter.visitMethod(ACC_PUBLIC, "<init>", "()V", null, null);
		methodVisitor.visitCode();
		Label label0 = new Label();
		methodVisitor.visitLabel(label0);
		methodVisitor.visitLineNumber(2, label0);
		methodVisitor.visitVarInsn(ALOAD, 0);
		methodVisitor.visitMethodInsn(INVOKESPECIAL, "java/lang/Object", "<init>", "()V", false);
		methodVisitor.visitInsn(RETURN);
		methodVisitor.visitMaxs(1, 1);
		methodVisitor.visitEnd();

		classWriter.visitEnd();
		return classWriter.toByteArray();
	}

	public static byte[] nestMemberWithNestHostAttribute () throws Exception {
		ClassWriter classWriter = new ClassWriter(0);

		classWriter.visit(V1_8, ACC_PUBLIC | ACC_SUPER, "NestMembers", null, "java/lang/Object", null);
		classWriter.visitSource("NestMembers.java", null);

		MethodVisitor methodVisitor;
		methodVisitor = classWriter.visitMethod(ACC_PUBLIC, "<init>", "()V", null, null);
		methodVisitor.visitCode();
		Label label0 = new Label();
		methodVisitor.visitLabel(label0);
		methodVisitor.visitLineNumber(2, label0);
		methodVisitor.visitVarInsn(ALOAD, 0);
		methodVisitor.visitMethodInsn(INVOKESPECIAL, "java/lang/Object", "<init>", "()V", false);
		methodVisitor.visitInsn(RETURN);
		methodVisitor.visitMaxs(1, 1);
		methodVisitor.visitEnd();

		NestHostAttribute attr = new NestHostAttribute("host");
		classWriter.visitAttribute(attr);

		classWriter.visitEnd();
		return classWriter.toByteArray();
	}

	public static byte[] nestHostWithAlteredNestMembersAttributeData () throws Exception {
		ClassWriter classWriter = new ClassWriter(0);

		classWriter.visit(V1_8, ACC_PUBLIC | ACC_SUPER, "NestHost", null, "java/lang/Object", null);
		classWriter.visitSource("NestHost.java", null);

		MethodVisitor methodVisitor;
		methodVisitor = classWriter.visitMethod(ACC_PUBLIC, "<init>", "()V", null, null);
		methodVisitor.visitCode();
		Label label0 = new Label();
		methodVisitor.visitLabel(label0);
		methodVisitor.visitLineNumber(2, label0);
		methodVisitor.visitVarInsn(ALOAD, 0);
		methodVisitor.visitMethodInsn(INVOKESPECIAL, "java/lang/Object", "<init>", "()V", false);
		methodVisitor.visitInsn(RETURN);
		methodVisitor.visitMaxs(1, 1);
		methodVisitor.visitEnd();

		String[] nestMembers = {"D", "E", "F"};
		NestMembersAttribute attr = new NestMembersAttribute(nestMembers);
		classWriter.visitAttribute(attr);

		classWriter.visitEnd();
		return classWriter.toByteArray();
	}

	public static byte[] nestHostWithAlteredNestMembersAttributeLength () throws Exception {
		ClassWriter classWriter = new ClassWriter(0);

		classWriter.visit(V1_8, ACC_PUBLIC | ACC_SUPER, "NestHost", null, "java/lang/Object", null);
		classWriter.visitSource("NestHost.java", null);

		MethodVisitor methodVisitor;
		methodVisitor = classWriter.visitMethod(ACC_PUBLIC, "<init>", "()V", null, null);
		methodVisitor.visitCode();
		Label label0 = new Label();
		methodVisitor.visitLabel(label0);
		methodVisitor.visitLineNumber(2, label0);
		methodVisitor.visitVarInsn(ALOAD, 0);
		methodVisitor.visitMethodInsn(INVOKESPECIAL, "java/lang/Object", "<init>", "()V", false);
		methodVisitor.visitInsn(RETURN);
		methodVisitor.visitMaxs(1, 1);
		methodVisitor.visitEnd();

		String[] nestMembers = {"A", "B"};
		NestMembersAttribute attr = new NestMembersAttribute(nestMembers);
		classWriter.visitAttribute(attr);

		classWriter.visitEnd();
		return classWriter.toByteArray();
	}

	public static byte[] nestMembersWithAlteredNestHostAttribute () throws Exception {
		ClassWriter classWriter = new ClassWriter(0);

		classWriter.visit(V1_8, ACC_PUBLIC | ACC_SUPER, "NestMembers", null, "java/lang/Object", null);
		classWriter.visitSource("NestMembers.java", null);

		MethodVisitor methodVisitor;
		methodVisitor = classWriter.visitMethod(ACC_PUBLIC, "<init>", "()V", null, null);
		methodVisitor.visitCode();
		Label label0 = new Label();
		methodVisitor.visitLabel(label0);
		methodVisitor.visitLineNumber(2, label0);
		methodVisitor.visitVarInsn(ALOAD, 0);
		methodVisitor.visitMethodInsn(INVOKESPECIAL, "java/lang/Object", "<init>", "()V", false);
		methodVisitor.visitInsn(RETURN);
		methodVisitor.visitMaxs(1, 1);
		methodVisitor.visitEnd();

		NestHostAttribute attr = new NestHostAttribute("AlteredHostName");
		classWriter.visitAttribute(attr);

		classWriter.visitEnd();
		return classWriter.toByteArray();
	}
}
