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

#include "IssueFinder.h"
#include <QRegExp>

void IssueFinder::findIssues(QString log)
{
    // WIN_RESTRICTIVE_DIRECTORY_PERMISSIONS
    addIssue(
            log.contains("Minecraft folder is:\nC:/Program Files/"),
            IssueType::WIN_RESTRICTIVE_DIRECTORY_PERMISSIONS
            );
    // MAC_JAVA_TOO_NEW
    addIssue(
            log.contains("Terminating app due to uncaught exception 'NSInternalInconsistencyException', reason: 'NSWindow drag regions should only be invalidated on the Main Thread!'"),
            IssueType::MAC_JAVA_TOO_NEW
            );
    // FORGE_JAVA_TOO_NEW
    addIssue(
            log.contains("java.lang.ClassCastException: class jdk.internal.loader.ClassLoaders$AppClassLoader cannot be cast to class java.net.URLClassLoader"),
            IssueType::FORGE_JAVA_TOO_NEW
    );
    // JAVA_ARCHITECTURE_MISMATCH
    addIssue(
            log.contains("Your Java architecture is not matching your system architecture."),
            IssueType::JAVA_ARCHITECTURE_MISMATCH
            );
    // FABRIC_MISSING_FABRIC_API
    addIssue(
            log.contains("java.lang.RuntimeException: Shaders Mod detected. Please remove it, OptiFine has built-in support for shaders."),
            IssueType::FABRIC_MISSING_FABRIC_API
    );
    // OUT_OF_MEMORY
    addIssue(
            log.contains("java.lang.OutOfMemoryError"),
            IssueType::OUT_OF_MEMORY
    );
    // WIN_INTEL_IGPU_NEEDS_OLDER_JAVA
    addIssue(
            log.contains(QRegExp("C  \\[(ig[0-9]+icd[0-9]+\\.dll)\\+(0x[0-9a-f]+)\\]")),
            IssueType::WIN_INTEL_IGPU_NEEDS_OLDER_JAVA
            );
    // FORGE_ID_LIMIT_EXCEEDED
    addIssue(
            log.contains("java.lang.RuntimeException: Invalid id 4096 - maximum id range exceeded."),
            IssueType::FORGE_ID_LIMIT_EXCEEDED
            );
    // WIN_LAUNCHER_IN_ONEDRIVE_FOLDER
    addIssue(
            log.contains(QRegExp("Minecraft folder is:\nC:/.+/.+/OneDrive")),
            IssueType::WIN_LAUNCHER_IN_ONEDRIVE_FOLDER
            );
    // SYSTEM_GLFW_USED
    addIssue(
            log.contains("Using system GLFW."),
            IssueType::SYSTEM_GLFW_USED
            );
    // SYSTEM_OPENAL_USED
    addIssue(
            log.contains("Using system OpenAL."),
            IssueType::SYSTEM_OPENAL_USED
            );
    // NOT_RECOMMENDED_JAVA_VERSION
    // OPTIFINE_SHADERMOD_CONFLICT
    addIssue(
            log.contains("java.lang.RuntimeException: Shaders Mod detected. Please remove it, OptiFine has built-in support for shaders."),
            IssueType::OPTIFINE_SHADERMOD_CONFLICT
    );
}

QString IssueFinder::shortReport()
{
    return QString("Issues found: %1").arg(issues_found.size());
}

QString IssueFinder::findResolution(IssueType type)
{
    switch (type) {
        default: return QString("No Resolution found");
    }
}

QString IssueFinder::fullReport()
{
    QString report = QString();

    for (IssueType type : issues_found.keys())
    {
        QString entry = QString("Issue ID: %1\nResolution: %2\n\n").arg(QString::number(type), findResolution(type));
        report += entry;
    }
    return report;
}

void IssueFinder::findLinesOfIssues(QString log)
{
    if (issue_bitmask == 0) return;

    QStringList lines = log.split('\n');

    for (int i = 0; i < lines.size(); i++)
    {

    }
}

void IssueFinder::addIssue(bool matches, IssueType type) {
    if (!matches) return;
    if (issues_found.contains(type)) return;

    issues_found.insert(type, QList<QString>());
    issue_bitmask += 1 << (unsigned int) type;
}
