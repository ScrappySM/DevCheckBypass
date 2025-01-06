# Ask the user for a project name.
$project = Read-Host "Enter the project name"
Write-Host "Project name is $project"

# Rename `ModTemplate.sln`, `ModTemplate.vcxproj`, `ModTemplate.vcxproj.filters`, and `ModTemplate.vcxproj.user` to the project name.
Rename-Item "ModTemplate.sln" "$project.sln"
Rename-Item "ModTemplate.vcxproj" "$project.vcxproj"
Rename-Item "ModTemplate.vcxproj.filters" "$project.vcxproj.filters"
Rename-Item "ModTemplate.vcxproj.user" "$project.vcxproj.user"

# Replace all instances of `ModTemplate` with the project name in the solution file.
$search = "ModTemplate"
$replace = $project

# Function to replace text in a file
function Replace-TextInFile {
    param (
        [string]$filePath,
        [string]$search,
        [string]$replace
    )

    # Read the file, replace text, and write the result to a temporary file
    $content = Get-Content $filePath
    $content = $content -replace $search, $replace
    $content | Set-Content "$filePath.tmp"

    # Delete the original file and rename the temporary file
    Remove-Item $filePath
    Rename-Item "$filePath.tmp" $filePath
}

# Replace text in the solution file
Replace-TextInFile "$project.sln" $search $replace

# Replace text in the project file
Replace-TextInFile "$project.vcxproj" $search $replace

# Replace text in .gitignore file
Replace-TextInFile ".gitignore" $search $replace

# Pause the script to allow the user to see the output (optional in PowerShell)
Read-Host -Prompt "Press Enter to continue"
