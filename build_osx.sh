cd godot-built

scons p=macos arch=arm64 target=editor module_mono_enabled=yes
scons p=macos arch=arm64 target=template_debug module_mono_enable=true
scons p=macos arch=arm64 target=template_release module_mono_enabled=true

bin/godot.macos.editor.arm64.mono --headless --generate-mono-glue modules/mono/glue
./modules/mono/build_scripts/build_assemblies.py --godot-output-dir=./bin --godot-platform=macos --push-nupkgs-local ~/Nuget
cd ..