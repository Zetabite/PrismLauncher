// SPDX-License-Identifier: Apache-2.0
/*
 *      Copyright 2013-2021 MultiMC Contributors
 *      Copyright 2022 Adrian Schmitz <zetabite.horzion@gmail.com>
 *
 *      Licensed under the Apache License, Version 2.0 (the "License");
 *      you may not use this file except in compliance with the License.
 *      You may obtain a copy of the License at
 *
 *          http://www.apache.org/licenses/LICENSE-2.0
 *
 *      Unless required by applicable law or agreed to in writing, software
 *      distributed under the License is distributed on an "AS IS" BASIS,
 *      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *      See the License for the specific language governing permissions and
 *      limitations under the License.
 */

#pragma once

#include <QMap>
#include <QString>

class IssueFinder
{
   public:
    // Naming: Optional[SYSTEM]_Optional[MOD_LOADER]_Optional[MC_VERSION]_[DESCRIPTION]
    //  SYSTEM: WIN, MAC, BSD, LIN (or a distro)
    //  MOD_LOADER: FORGE, RIFT, QUILT, FABRIC, LITELOADER
    // Example: WIN_FABRIC_SKILL_ISSUE, DOWNRIGHT_EVIL_BIT_SHIFTING, MACOS_1_17_STEVE_JOBS_REVIVED

    enum IssueType
    {
        // Errors
        // Issues that cause an instance not work at all, or shouldn't exist in the first place, like bad practices
        WIN_RESTRICTIVE_DIRECTORY_PERMISSIONS,
        MAC_JAVA_TOO_NEW,
        FORGE_JAVA_TOO_NEW,
        JAVA_ARCHITECTURE_MISMATCH,
        FABRIC_MISSING_FABRIC_API,
        OUT_OF_MEMORY,
        WIN_INTEL_IGPU_NEEDS_OLDER_JAVA,
        FORGE_ID_LIMIT_EXCEEDED,

        // Warnings
        // Issues that can cause an instance to not work, but not necessary cause it to not work.
        WIN_LAUNCHER_IN_ONEDRIVE_FOLDER,
        SYSTEM_GLFW_USED,
        SYSTEM_OPENAL_USED,
        NOT_RECOMMENDED_JAVA_VERSION,
        OPTIFINE_SHADERMOD_CONFLICT
    };

    void findIssues(QString log);

    QString shortReport();
    QString fullReport();

    QString findResolution(IssueType type);

   private:
    // Entry: ErrorType/WarningType, Found on Lines
    QMap<IssueType, QList<QString>> issues_found;

    unsigned int issue_bitmask = 0;

    // Find lines of issues
    void findLinesOfIssues(QString log);

    void addIssue(bool matches, IssueType type);
};
