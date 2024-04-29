# dotnet nuget add source ~/Nuget
scons p=windows target=editor module_mono_enabled=yes
scons p=windows target=template_debug module_mono_enable=true
scons p=windows target=template_release module_mono_enabled=true

bin/godot.windows.editor.x86_64.mono --headless --generate-mono-glue modules/mono/glue
python ./modules/mono/build_scripts/build_assemblies.py --godot-output-dir=./bin --godot-platform=macos --push-nupkgs-local /Nuget
