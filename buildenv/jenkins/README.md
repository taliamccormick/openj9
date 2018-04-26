<!--
Copyright (c) 2017, 2018 IBM Corp. and others

This program and the accompanying materials are made available under
the terms of the Eclipse Public License 2.0 which accompanies this
distribution and is available at https://www.eclipse.org/legal/epl-2.0/
or the Apache License, Version 2.0 which accompanies this distribution and
is available at https://www.apache.org/licenses/LICENSE-2.0.

This Source Code may also be made available under the following
Secondary Licenses when the conditions for such availability set
forth in the Eclipse Public License, v. 2.0 are satisfied: GNU
General Public License, version 2 with the GNU Classpath
Exception [1] and GNU General Public License, version 2 with the
OpenJDK Assembly Exception [2].

[1] https://www.gnu.org/software/classpath/license.html
[2] http://openjdk.java.net/legal/assembly-exception.html

SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0 WITH Classpath-exception-2.0 OR LicenseRef-GPL-2.0 WITH Assembly-exception
-->

[Eclipse OpenJ9 Jenkins Builds](https://ci.eclipse.org/openj9/)

This folder contains Jenkins pipeline scripts that are used in the OpenJ9 Jenkins builds.

### Triggering Pull Request Builds from Github

- You can request a PR build to do compile or compile & test
- Current supported test levels are functional sanity and functional extended
- Current available platforms are 
    - Linux s390x (zLinux)
    - Linux PPCLE (pLinux)
    - AIX PPC (aix)
- Current supported Java verisons are Java8 and Java9
- OpenJ9 committers can request builds by commenting in a pull request
    - Format: `Jenkins <build type> <level> <platform(s)> <java version(s)>`
    - Build Types: compile,test
    - Levels: sanity,extended (only if Build Type is test)
    - Platforms: zlinux,plinux,aix
    - Java Versions: jdk8,jdk9,jdk10
- Note: You can use keyword `all` for level, platform or version


###### Examples
- Request a Compile-only build on all platforms and all java versions by commenting in a PR
    - `Jenkins compile`
    - `Jenkins compile all all`
- Request a Sanity build on zLinux all java versions
    - `Jenkins test sanity zlinux`
    - `Jenkins test sanity zlinux all`
- Request an Extended build on pLinux java8 only
    - `Jenkins test extended plinux jdk8`
- Request a Sanity build on z,p Linux on java 8,9
    - `Jenkins test sanity zlinux,plinux jdk8,jdk9`
- Request all tests on all platforms all java versions
    - `Jenkins test all`
    - `Jenkins test all all all`

You can also request a Pull Request build from the extensions repos or openj9-omr
- [openj9-omr](https://github.com/eclipse/openj9-omr)
- [openj9-openjdk-jdk8](https://github.com/ibmruntimes/openj9-openjdk-jdk8)
- [openj9-openjdk-jdk9](https://github.com/ibmruntimes/openj9-openjdk-jdk9)

###### Note: When specifying a dependent change in an OpenJDK extensions repo, you can only build the SDK version that matches the repo where the dependent change lives. Eg. You cannot build JDK8 with a PR in openj9-openjdk-jdk9.

##### Dependent Changes

- If you have dependent change(s) in either eclipse/omr, eclipse/openj9-omr, or ibmruntimes/openj9-openjdk-jdk\*, you can build & test with all needed changes
- Request a build by including the PR ref in your trigger comment
- Ex. Dependent change in OMR Pull Request `#123`
    - `Jenkins test sanity depends eclipse/omr#123`
- Ex. Dependent change in OpenJ9-OMR Pull Request `#456`
    - `Jenkins test sanity depends eclipse/openj9-omr#456`
- Ex. Dependent change in OpenJDK Pull Request `#789`
    - `Jenkins test sanity depends ibmruntimes/openj9-openjdk-jdk9#789`
- Ex. Dependent changes in OMR and OpenJDK
    - `Jenkins test sanity all jdk9 depends eclipse/omr#123 ibmruntimes/openj9-openjdk-jdk9#789`
- Ex. If you have a dependent change and only want one platform, depends comes last
    - `Jenkins test sanity zlinux all depends eclipse/omr#123`

##### Special Pull Requests builds

- To trigger a Valhalla Nestmates PR build:
   - `Jenkins test sanity plinux jdk11-nestmates`

##### Other Pull Requests builds

- To trigger a Line Endings Check
   - `Jenkins line endings check`

- To trigger a Copyright Check
   - `Jenkins copyright check`

### Overview of Builds

#### Build

- Build-JDK8-aix_ppc-64_cmprssptrs
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Build-JDK8-linux_390-64_cmprssptrs)](https://ci.eclipse.org/openj9/job/Build-JDK8-aix_ppc-64_cmprssptrs)
    - Description:
        - Compiles java8 on aix_ppc-64_cmprssptrs
        - Archives the SDK and test material for use in downstream jobs
    - Trigger:
        - This job is used in other pipelines but can be launched manually

- Build-JDK9-aix_ppc-64_cmprssptrs
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Build-JDK9-linux_390-64_cmprssptrs)](https://ci.eclipse.org/openj9/job/Build-JDK9-aix_ppc-64_cmprssptrs)
    - Description:
        - Compiles java9 on aix_ppc-64_cmprssptrs
        - Archives the SDK and test material for use in downstream jobs
    - Trigger:
        - This job is used in other pipelines but can be launched manually

- Build-JDK10-aix_ppc-64_cmprssptrs
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Build-JDK10-linux_390-64_cmprssptrs)](https://ci.eclipse.org/openj9/job/Build-JDK10-aix_ppc-64_cmprssptrs)
    - Description:
        - Compiles java10 on aix_ppc-64_cmprssptrs
        - Archives the SDK and test material for use in downstream jobs
    - Trigger:
        - This job is used in other pipelines but can be launched manually

- Build-JDK8-linux_390-64_cmprssptrs
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Build-JDK8-linux_390-64_cmprssptrs)](https://ci.eclipse.org/openj9/job/Build-JDK8-linux_390-64_cmprssptrs)
    - Description:
        - Compiles java8 on linux_390-64_cmprssptrs
        - Archives the SDK and test material for use in downstream jobs
    - Trigger:
        - This job is used in other pipelines but can be launched manually

- Build-JDK9-linux_390-64_cmprssptrs
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Build-JDK9-linux_390-64_cmprssptrs)](https://ci.eclipse.org/openj9/job/Build-JDK9-linux_390-64_cmprssptrs)
    - Description:
        - Compiles java9 on linux_390-64_cmprssptrs
        - Archives the SDK and test material for use in downstream jobs
    - Trigger:
        - This job is used in other pipelines but can be launched manually

- Build-JDK10-linux_390-64_cmprssptrs
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Build-JDK10-linux_390-64_cmprssptrs)](https://ci.eclipse.org/openj9/job/Build-JDK10-linux_390-64_cmprssptrs)
    - Description:
        - Compiles java10 on linux_390-64_cmprssptrs
        - Archives the SDK and test material for use in downstream jobs
    - Trigger:
        - This job is used in other pipelines but can be launched manually

- Build-JDK8-linux_ppc-64_cmprssptrs_le
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Build-JDK8-linux_ppc-64_cmprssptrs_le)](https://ci.eclipse.org/openj9/job/Build-JDK8-linux_ppc-64_cmprssptrs_le)
    - Description
        - Compiles java8 on linux_ppc-64_cmprssptrs_le
        - Archives the SDK and test material for use in downstream jobs
    - Trigger:
        - This job is used in other pipelines but can be launched manually

- Build-JDK9-linux_ppc-64_cmprssptrs_le
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Build-JDK9-linux_ppc-64_cmprssptrs_le)](https://ci.eclipse.org/openj9/job/Build-JDK9-linux_ppc-64_cmprssptrs_le)
    - Description
        - Compiles java9 on linux_ppc-64_cmprssptrs_le
        - Archives the SDK and test material for use in downstream jobs
    - Trigger:
        - This job is used in other pipelines but can be launched manually

- Build-JDK10-linux_ppc-64_cmprssptrs_le
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Build-JDK10-linux_ppc-64_cmprssptrs_le)](https://ci.eclipse.org/openj9/job/Build-JDK10-linux_ppc-64_cmprssptrs_le)
    - Description
        - Compiles java10 on linux_ppc-64_cmprssptrs_le
        - Archives the SDK and test material for use in downstream jobs
    - Trigger:
        - This job is used in other pipelines but can be launched manually

- Build-JDK11-linux_ppc-64_cmprssptrs_le_valhalla_nestmates
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Build-JDK11-linux_ppc-64_cmprssptrs_le_valhalla_nestmates)](https://ci.eclipse.org/openj9/job/Build-JDK11-linux_ppc-64_cmprssptrs_le_valhalla_nestmates)
    - Description
        - Compiles java11 with nestmates on linux_ppc-64_cmprssptrs_le
        - Archives the SDK and test material for use in downstream jobs
    - Trigger:
        - This job is used in other pipelines but can be launched manually

#### Infrastructure

- Mirror-OMR-to-OpenJ9-OMR
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Mirror-OMR-to-OpenJ9-OMR)](https://ci.eclipse.org/openj9/job/Mirror-OMR-to-OpenJ9-OMR)
    - Description:
        - Mirrors [eclipse/omr/master](https://github.com/eclipse/omr/tree/master) to [eclipse/openj9-omr/master](https://github.com/eclipse/openj9-omr/tree/master)
        - Triggers `Pipeline-OMR-Acceptance` when there is new content        
    - Trigger:
        - Build periodically, 15 minutes

- Promote-OpenJ9-OMR-master-to-openj9
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Promote-OpenJ9-OMR-master-to-openj9)](https://ci.eclipse.org/openj9/job/Promote-OpenJ9-OMR-master-to-openj9)
    - Description:
        - Promotes eclipse/openj9-omr branch master to branch openj9
        - Lays a tag down on the promoted SHA in the format `omr_merge_YYYYMMDD_HHMMSS` with annotations including the current OpenJ9 and OpenJDK SHAs
    - Trigger:
        - Last step of `Pipeline-OMR-Acceptance`

- Mirror-OpenJ9-Website-to-Eclipse
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Mirror-OpenJ9-Website-to-Eclipse)](https://ci.eclipse.org/openj9/job/Mirror-OpenJ9-Website-to-Eclipse)
    - Description:
        - Mirrors [github.com/eclipse/openj9-website](https://github.com/eclipse/openj9-website/tree/master) to the Eclipse.org repo
    - Trigger:
        - Poll Github repo for changes
 
#### Pipelines

- Pipeline-Build-Test-JDK8-aix_ppc-64_cmprssptrs
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Pipeline-Build-Test-JDK8-aix_ppc-64_cmprssptrs)](https://ci.eclipse.org/openj9/job/Pipeline-Build-Test-JDK8-aix_ppc-64_cmprssptrs)
    - Description:
        - Compile and Test java8 Sanity & Extended
        - Triggers
            - `Build-JDK8-aix_ppc-64_cmprssptrs`
            - `Test-Sanity-JDK8-aix_ppc-64_cmprssptrs`
            - `Test-Extended-JDK8-aix_ppc-64_cmprssptrs`

    - Trigger:
        - build periodically, @midnight

- Pipeline-Build-Test-JDK9-aix_ppc-64_cmprssptrs
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Pipeline-Build-Test-JDK9-aix_ppc-64_cmprssptrs)](https://ci.eclipse.org/openj9/job/Pipeline-Build-Test-JDK9-aix_ppc-64_cmprssptrs)
    - Description:
        - Compile and Test java9 Sanity & Extended
        - Triggers
            - `Build-JDK9-aix_ppc-64_cmprssptrs`
            - `Test-Sanity-JDK9-aix_ppc-64_cmprssptrs`
            - `Test-Extended-JDK9-aix_ppc-64_cmprssptrs`

    - Trigger:
        - build periodically, @midnight

- Pipeline-Build-Test-JDK10-aix_ppc-64_cmprssptrs
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Pipeline-Build-Test-JDK10-aix_ppc-64_cmprssptrs)](https://ci.eclipse.org/openj9/job/Pipeline-Build-Test-JDK10-aix_ppc-64_cmprssptrs)
    - Description:
        - Compile and Test java10 Sanity & Extended
        - Triggers
            - `Build-JDK10-aix_ppc-64_cmprssptrs`
            - `Test-Sanity-JDK10-aix_ppc-64_cmprssptrs`
            - `Test-Extended-JDK10-aix_ppc-64_cmprssptrs`

    - Trigger:
        - build periodically, @midnight

- Pipeline-Build-Test-JDK8-linux_390-64_cmprssptrs
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Pipeline-Build-Test-JDK8-linux_390-64_cmprssptrs)](https://ci.eclipse.org/openj9/job/Pipeline-Build-Test-JDK8-linux_390-64_cmprssptrs)
    - Description:
        - Compile and Test java8 Sanity & Extended
        - Triggers
            - `Build-JDK8-linux_390-64_cmprssptrs`
            - `Test-Sanity-JDK8-linux_390-64_cmprssptrs`
            - `Test-Extended-JDK8-linux_390-64_cmprssptrs`

    - Trigger:
        - build periodically, @midnight

- Pipeline-Build-Test-JDK9-linux_390-64_cmprssptrs
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Pipeline-Build-Test-JDK9-linux_390-64_cmprssptrs)](https://ci.eclipse.org/openj9/job/Pipeline-Build-Test-JDK9-linux_390-64_cmprssptrs)
    - Description:
        - Compile and Test java9 Sanity & Extended
        - Triggers
            - `Build-JDK9-linux_390-64_cmprssptrs`
            - `Test-Sanity-JDK9-linux_390-64_cmprssptrs`
            - `Test-Extended-JDK9-linux_390-64_cmprssptrs`

    - Trigger:
        - build periodically, @midnight

- Pipeline-Build-Test-JDK10-linux_390-64_cmprssptrs
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Pipeline-Build-Test-JDK10-linux_390-64_cmprssptrs)](https://ci.eclipse.org/openj9/job/Pipeline-Build-Test-JDK10-linux_390-64_cmprssptrs)
    - Description:
        - Compile and Test java10 Sanity & Extended
        - Triggers
            - `Build-JDK10-linux_390-64_cmprssptrs`
            - `Test-Sanity-JDK10-linux_390-64_cmprssptrs`
            - `Test-Extended-JDK10-linux_390-64_cmprssptrs`

    - Trigger:
        - build periodically, @midnight

- Pipeline-Build-Test-JDK8-linux_ppc-64_cmprssptrs_le
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Pipeline-Build-Test-JDK8-linux_ppc-64_cmprssptrs_le)](https://ci.eclipse.org/openj9/job/Pipeline-Build-Test-JDK8-linux_ppc-64_cmprssptrs_le)
    - Description:
        - Compile and Test java8 Sanity & Extended
        - Triggers
            - `Build-JDK8-linux_ppc-64_cmprssptrs_le`
            - `Test-Sanity-JDK8-linux_ppc-64_cmprssptrs_le`
            - `Test-Extended-JDK8-linux_ppc-64_cmprssptrs_le`
    - Trigger:
        - build periodically, @midnight

- Pipeline-Build-Test-JDK9-linux_ppc-64_cmprssptrs_le
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Pipeline-Build-Test-JDK9-linux_ppc-64_cmprssptrs_le)](https://ci.eclipse.org/openj9/job/Pipeline-Build-Test-JDK9-linux_ppc-64_cmprssptrs_le)
    - Description:
        - Compile and Test java9 Sanity & Extended
        - Triggers
            - `Build-JDK9-linux_ppc-64_cmprssptrs_le`
            - `Test-Sanity-JDK9-linux_ppc-64_cmprssptrs_le`
            - `Test-Extended-JDK9-linux_ppc-64_cmprssptrs_le`
    - Trigger:
        - build periodically, @midnight

- Pipeline-Build-Test-JDK10-linux_ppc-64_cmprssptrs_le
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Pipeline-Build-Test-JDK10-linux_ppc-64_cmprssptrs_le)](https://ci.eclipse.org/openj9/job/Pipeline-Build-Test-JDK10-linux_ppc-64_cmprssptrs_le)
    - Description:
        - Compile and Test java10 Sanity & Extended
        - Triggers
            - `Build-JDK10-linux_ppc-64_cmprssptrs_le`
            - `Test-Sanity-JDK10-linux_ppc-64_cmprssptrs_le`
            - `Test-Extended-JDK10-linux_ppc-64_cmprssptrs_le`
    - Trigger:
        - build periodically, @midnight

- Pipeline-OMR-Acceptance
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Pipeline-OMR-Acceptance)](https://ci.eclipse.org/openj9/job/Pipeline-OMR-Acceptance)
    - Description:
        - Compile and Test Sanity against new OMR content
        - Triggers
            - `Build-linux_390-64_cmprssptrs`
            - `Build-linux_ppc-64_cmprssptrs_le`
            - `Test-Sanity-linux_390-64_cmprssptrs`
            - `Test-Sanity-linux_ppc-64_cmprssptrs_le`
            - `Promote-OpenJ9-OMR-master-to-openj9`
    - Trigger: Triggered by `Mirror-OMR-to-OpenJ9-OMR`

#### Pull Requests
###### **REPO** indicates the job is configured for Pull Requests from that repository. Can be one of openj9, openj9-omr, openj9-openjdk-jdk8 etc.
###### **VERSION** indicates the job is configured for each JDK version. Can be one of 8,9,10 etc.
###### **SPEC** indicates the job is configured for each platform spec. Can be one of aix_ppc-64_cmprssptrs, linux_ppc-64_cmprssptrs_le, linux_390-64_cmprssptrs etc.

- PullRequest-Compile-JDK**VERSION**-**SPEC**-**REPO**
    - Description:
        - Compile java **VERSION** on platform **SPEC**
    - Trigger:
        - Github PR comment example `Jenkins compile <SPEC> jdk<VERSION>`

- PullRequest-Extended-JDK**VERSION**-**SPEC**-**REPO**
    - Description:
        - Compile and Extended tests java **VERSION** on platform **SPEC**
    - Trigger:
        - Github PR comment `Jenkins test extended <SPEC> jdk<VERSION>`

- PullRequest-Sanity-JDK**VERSION**-**SPEC**-**REPO**
    - Description:
        - Compile and Sanity tests java **VERSION** on platform **SPEC**
    - Trigger:
        - Github PR comment `Jenkins test sanity <SPEC> jdk<VERSION>`

- PullRequest-LineEndingsCheck-**REPO**
    - Description:
        - Checks the files modified in a pull request have correct line endings
    - Trigger:
        - Automatically builds on every PR
        - Retrigger with `Jenkins line endings check`

- PullRequest-CopyrightCheck-**REPO**
    - Description:
        - Checks the files modified in a pull request have copyright with current year
    - Trigger:
        - Automatically builds on every PR
        - Retrigger with `Jenkins copyright check`

#### Test

- Test-Extended-JDK8-aix_ppc-64_cmprssptrs
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Test-Extended-JDK8-aix_ppc-64_cmprssptrs)](https://ci.eclipse.org/openj9/job/Test-Extended-JDK8-aix_ppc-64_cmprssptrs)
    - Description:
        - Runs extended test suite against the SDK and test material that is passed as parameters
    - Trigger:
        - This job is used in other pipelines but can be launched manually

- Test-Extended-JDK9-aix_ppc-64_cmprssptrs
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Test-Extended-JDK9-aix_ppc-64_cmprssptrs)](https://ci.eclipse.org/openj9/job/Test-Extended-JDK9-aix_ppc-64_cmprssptrs)
    - Description:
        - Runs extended test suite against the SDK and test material that is passed as parameters
    - Trigger:
        - This job is used in other pipelines but can be launched manually

- Test-Extended-JDK10-aix_ppc-64_cmprssptrs
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Test-Extended-JDK10-aix_ppc-64_cmprssptrs)](https://ci.eclipse.org/openj9/job/Test-Extended-JDK10-aix_ppc-64_cmprssptrs)
    - Description:
        - Runs extended test suite against the SDK and test material that is passed as parameters
    - Trigger:
        - This job is used in other pipelines but can be launched manually

- Test-Extended-JDK8-linux_390-64_cmprssptrs
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Test-Extended-JDK8-linux_390-64_cmprssptrs)](https://ci.eclipse.org/openj9/job/Test-Extended-JDK8-linux_390-64_cmprssptrs)
    - Description:
        - Runs extended test suite against the SDK and test material that is passed as parameters
    - Trigger:
        - This job is used in other pipelines but can be launched manually

- Test-Extended-JDK9-linux_390-64_cmprssptrs
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Test-Extended-JDK9-linux_390-64_cmprssptrs)](https://ci.eclipse.org/openj9/job/Test-Extended-JDK9-linux_390-64_cmprssptrs)
    - Description:
        - Runs extended test suite against the SDK and test material that is passed as parameters
    - Trigger:
        - This job is used in other pipelines but can be launched manually

- Test-Extended-JDK10-linux_390-64_cmprssptrs
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Test-Extended-JDK10-linux_390-64_cmprssptrs)](https://ci.eclipse.org/openj9/job/Test-Extended-JDK10-linux_390-64_cmprssptrs)
    - Description:
        - Runs extended test suite against the SDK and test material that is passed as parameters
    - Trigger:
        - This job is used in other pipelines but can be launched manually

- Test-Extended-JDK8-linux_ppc-64_cmprssptrs_le
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Test-Extended-JDK8-linux_ppc-64_cmprssptrs_le)](https://ci.eclipse.org/openj9/job/Test-Extended-JDK8-linux_ppc-64_cmprssptrs_le)
    - Description:
        - Runs extended test suite against the SDK and test material that is passed as parameters
    - Trigger:
        - This job is used in other pipelines but can be launched manually

- Test-Extended-JDK9-linux_ppc-64_cmprssptrs_le
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Test-Extended-JDK9-linux_ppc-64_cmprssptrs_le)](https://ci.eclipse.org/openj9/job/Test-Extended-JDK9-linux_ppc-64_cmprssptrs_le)
    - Description:
        - Runs extended test suite against the SDK and test material that is passed as parameters
    - Trigger:
        - This job is used in other pipelines but can be launched manually

- Test-Extended-JDK10-linux_ppc-64_cmprssptrs_le
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Test-Extended-JDK10-linux_ppc-64_cmprssptrs_le)](https://ci.eclipse.org/openj9/job/Test-Extended-JDK10-linux_ppc-64_cmprssptrs_le)
    - Description:
        - Runs extended test suite against the SDK and test material that is passed as parameters
    - Trigger:
        - This job is used in other pipelines but can be launched manually

- Test-Sanity-JDK8-aix_ppc-64_cmprssptrs
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Test-Sanity-JDK8-aix_ppc-64_cmprssptrs)](https://ci.eclipse.org/openj9/job/Test-Sanity-JDK8-aix_ppc-64_cmprssptrs)
    - Description:
        - Runs sanity test suite against the SDK and test material that is passed as parameters
    - Trigger:
        - This job is used in other pipelines but can be launched manually

- Test-Sanity-JDK9-aix_ppc-64_cmprssptrs
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Test-Sanity-JDK9-aix_ppc-64_cmprssptrs)](https://ci.eclipse.org/openj9/job/Test-Sanity-JDK9-aix_ppc-64_cmprssptrs)
    - Description:
        - Runs sanity test suite against the SDK and test material that is passed as parameters
    - Trigger:
        - This job is used in other pipelines but can be launched manually

- Test-Sanity-JDK10-aix_ppc-64_cmprssptrs
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Test-Sanity-JDK10-aix_ppc-64_cmprssptrs)](https://ci.eclipse.org/openj9/job/Test-Sanity-JDK10-aix_ppc-64_cmprssptrs)
    - Description:
        - Runs sanity test suite against the SDK and test material that is passed as parameters
    - Trigger:
        - This job is used in other pipelines but can be launched manually

- Test-Sanity-JDK8-linux_390-64_cmprssptrs
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Test-Sanity-JDK8-linux_390-64_cmprssptrs)](https://ci.eclipse.org/openj9/job/Test-Sanity-JDK8-linux_390-64_cmprssptrs)
    - Description:
        - Runs sanity test suite against the SDK and test material that is passed as parameters
    - Trigger:
        - This job is used in other pipelines but can be launched manually

- Test-Sanity-JDK9-linux_390-64_cmprssptrs
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Test-Sanity-JDK9-linux_390-64_cmprssptrs)](https://ci.eclipse.org/openj9/job/Test-Sanity-JDK9-linux_390-64_cmprssptrs)
    - Description:
        - Runs sanity test suite against the SDK and test material that is passed as parameters
    - Trigger:
        - This job is used in other pipelines but can be launched manually

- Test-Sanity-JDK10-linux_390-64_cmprssptrs
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Test-Sanity-JDK10-linux_390-64_cmprssptrs)](https://ci.eclipse.org/openj9/job/Test-Sanity-JDK10-linux_390-64_cmprssptrs)
    - Description:
        - Runs sanity test suite against the SDK and test material that is passed as parameters
    - Trigger:
        - This job is used in other pipelines but can be launched manually

- Test-Sanity-JDK8-linux_ppc-64_cmprssptrs_le
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Test-Sanity-JDK8-linux_ppc-64_cmprssptrs_le)](https://ci.eclipse.org/openj9/job/Test-Sanity-JDK8-linux_ppc-64_cmprssptrs_le)
    - Description:
        - Runs sanity test suite against the SDK and test material that is passed as parameters
    - Trigger:
        - This job is used in other pipelines but can be launched manually

- Test-Sanity-JDK9-linux_ppc-64_cmprssptrs_le
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Test-Sanity-JDK9-linux_ppc-64_cmprssptrs_le)](https://ci.eclipse.org/openj9/job/Test-Sanity-JDK9-linux_ppc-64_cmprssptrs_le)
    - Description:
        - Runs sanity test suite against the SDK and test material that is passed as parameters
    - Trigger:
        - This job is used in other pipelines but can be launched manually

- Test-Sanity-JDK10-linux_ppc-64_cmprssptrs_le
    - [![Build Status](https://ci.eclipse.org/openj9/buildStatus/icon?job=Test-Sanity-JDK10-linux_ppc-64_cmprssptrs_le)](https://ci.eclipse.org/openj9/job/Test-Sanity-JDK10-linux_ppc-64_cmprssptrs_le)
    - Description:
        - Runs sanity test suite against the SDK and test material that is passed as parameters
    - Trigger:
        - This job is used in other pipelines but can be launched manually

### Adding Builds
- Always add pipeline style jobs so the code can be committed to the repo once it is ready
- Update this readme when your build is in production use
- Whenever possible, reuse existing builds or existing jenkins files
