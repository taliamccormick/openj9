/*******************************************************************************
 * Copyright (c) 2001, 2017 IBM Corp. and others
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
package jit.test.jitt.cfg;

import org.testng.annotations.Test;

@Test(groups = { "level.sanity","component.jit" })
public class nestedExceptions extends jit.test.jitt.Test {
   int tstExcp(int i) {
      try {
         if (i > 10)
            throw new Exception();
      }
      catch(Exception e1) {
         try {
            if (i > 11)
               throw new Exception();
         }
         catch(Exception e2) {
            try {
               if (i > 12)
                  throw new Exception();
            }
            catch(Exception e3) {  
               i = 99;
            }
         }
      }
      return i;
   };
   
   @Test
   public void testnestedExceptions() {
		tstExcp(0);
		for (int i = 0; i < sJitThreshold; i++) {
			tstExcp(0);
		}
		tstExcp(0);
	}

   }