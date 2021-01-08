# Don't allow our script to continue if any errors are observed
$ErrorActionPreference = "Stop"

Write-Host "Windows setup starting"

# Check that we have a 'third-party' folder
Push-Location -Path "..\..\"
if (!(Test-Path "third-party")) {
	New-Item -ItemType Directory -Path "third-party"
} else {
    Write-Host "third-party folder already exists"
}
Pop-Location

# Check that we have the SDL2 third party Windows dev library
if (!(Test-Path "..\..\third-party\sdl-windows")) {
	Write-Host "Downloading SDL Windows Dev library into third party folder sdl-windows ..."
    $url = "https://www.libsdl.org/release/SDL2-devel-2.0.9-VC.zip"
    $path = "..\..\third-party\SDL2-devel-2.0.9-VC.zip"
	$WebClient = New-Object System.Net.WebClient
	$WebClient.DownloadFile($url, $path)

	Push-Location -Path "..\..\third-party"
		Write-Host "Unzipping SDL Windows Dev library into third-party\sdl-windows ..."
		cmd.exe /c 'tar -xf SDL2-devel-2.0.9-VC.zip'
		Move-Item -Path SDL2-2.0.9 -Destination sdl-windows
		Remove-Item -Path SDL2-devel-2.0.9-VC.zip
	Pop-Location
} else {
    Write-Host "SDL-Windows already exists"
}

# Check that we have the GLEW third party library
if (!(Test-Path "..\..\third-party\glew")) {
	Write-Host "Downloading GLEW into third party folder glew ..."
	$WebClient = New-Object System.Net.WebClient
	$WebClient.DownloadFile("https://github.com/nigels-com/glew/releases/download/glew-2.1.0/glew-2.1.0-win32.zip", "..\..\third-party\glew-2.1.0-win32.zip")

	Push-Location -Path "..\..\third-party"
		Write-Host "Unzipping GLEW library into third-party\glew ..."
		cmd.exe /c 'tar -xf glew-2.1.0-win32.zip'
		Move-Item -Path glew-2.1.0 -Destination glew
		Remove-Item -Path glew-2.1.0-win32.zip
	Pop-Location
} else {
    Write-Host "GLEW already exists"
}

# Check that we have the GLM third party library
if (!(Test-Path "..\..\third-party\glm")) {
	Write-Host "Downloading GLM into third party folder glm ..."
	$WebClient = New-Object System.Net.WebClient
	$WebClient.DownloadFile("https://github.com/g-truc/glm/releases/download/0.9.9.3/glm-0.9.9.3.zip", "..\..\third-party\glm-0.9.9.3.zip")

	Push-Location -Path "..\..\third-party"
		Write-Host "Unzipping GLM into third-party\glm ..."
		cmd.exe /c 'tar -xf glm-0.9.9.3.zip'
		Remove-Item -Path glm-0.9.9.3.zip
	Pop-Location
} else {
    Write-Host "GLM already exists"
}

# Check that we have the Tiny OBJ Loader third party library
if (!(Test-Path "..\..\third-party\tiny-obj-loader")) {
	Write-Host "Downloading Tiny OBJ Loader into third party folder tiny-obj-loader ..."
	$WebClient = New-Object System.Net.WebClient
	$WebClient.DownloadFile("https://github.com/tinyobjloader/tinyobjloader/archive/v2.0-rc1.zip", "..\..\third-party\tiny-obj-loader-v2.0-rc1.zip")

	Push-Location -Path "..\..\third-party"
		Write-Host "Unzipping Tiny OBJ Loader into third-party\tiny-obj-loader ..."
		cmd.exe /c 'tar -xf tiny-obj-loader-v2.0-rc1.zip'
		Move-Item -Path tinyobjloader-2.0-rc1 -Destination tiny-obj-loader
		Remove-Item -Path tiny-obj-loader-v2.0-rc1.zip
	Pop-Location
} else {
    Write-Host "Tiny Obj Loader already exists"
}

# Check that we have the SDL2_image third party Windows dev library
if (!(Test-Path "..\..\third-party\sdl-image-windows")) {
	Write-Host "Downloading SDL Image Windows library into third party folder sdl-image-windows ..."
	$WebClient = New-Object System.Net.WebClient
	$WebClient.DownloadFile("https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.4-VC.zip", "..\..\third-party\SDL2_image-devel-2.0.4-VC.zip")

	Push-Location -Path "..\..\third-party"
		Write-Host "Unzipping SDL Image Windows library into third-party\sdl-image-windows ..."
		cmd.exe /c 'tar -xf SDL2_image-devel-2.0.4-VC.zip'
		Move-Item -Path SDL2_image-2.0.4 -Destination sdl-image-windows
		Remove-Item -Path SDL2_image-devel-2.0.4-VC.zip
	Pop-Location
} else {
    Write-Host "SDL-image-windows already exists"
}

#Compile Vulkan shaders into SPIR-V binary assets.
Push-Location -Path "../../vulkan_shader_source"
    .\compile_shaders.ps1
Pop-Location

# Check that we have Lua third party Windows
if (!(Test-Path "..\..\third-party\lua")) {
    Write-Host "Downloading Lua library into third party folder lua ..."
    $WebClient = New-Object System.Net.WebClient
    $WebClient.DownloadFile("https://github.com/lua/lua/archive/v5.3.zip", "..\..\third-party\lua-5.3.zip")

    Push-Location -Path "..\..\third-party"
        Write-Host "Unzipping Lua library into third-party\lua ..."
        cmd.exe /c 'tar -xf lua-5.3.zip'
        Move-Item -Path lua-5.3 -Destination lua
        Remove-Item -Path lua-5.3.zip
        Write-Host "Lua extracted and setup ..."
    Pop-Location
} else {
    Write-Host "Lua already exists"
}

# Check that we have imgui third party lib
if (!(Test-Path "..\..\third-party\imgui")) {
    Write-Host "Downloading Lua library into third party folder lua ..."
    $WebClient = New-Object System.Net.WebClient
    $WebClient.DownloadFile("https://github.com/ocornut/imgui/archive/docking.zip", "..\..\third-party\imgui-docking.zip")

    Push-Location -Path "..\..\third-party"
        Write-Host "Unzipping ImGUI library into third-party\ImGUI ..."
        cmd.exe /c 'tar -xf imgui-docking.zip'
        Move-Item -Path imgui-docking -Destination imgui
        Remove-Item -Path imgui-docking.zip
        Write-Host "ImGUI extracted and setup ..."
    Pop-Location
} else {
    Write-Host "ImGUI already exists"
}

# Check that we have nlohmann json third party lib
if (!(Test-Path "..\..\third-party\json")) {
	Write-Host "Downloading Json library into third party folder json ..."
    $WebClient = New-Object System.Net.WebClient
    $WebClient.DownloadFile("https://github.com/nlohmann/json/archive/v3.9.1.zip", "..\..\third-party\v3.9.1.zip")

    Push-Location -Path "..\..\third-party"
        Write-Host "Unzipping json library into third-party\json ..."
        cmd.exe /c 'tar -xf v3.9.1.zip'
        Move-Item -Path json-3.9.1 -Destination json
        Remove-Item -Path v3.9.1.zip
        Write-Host "Json extracted and setup ..."
    Pop-Location
} else {
    Write-Host "Json already exists"
}

Write-Host "Windows setup complete"