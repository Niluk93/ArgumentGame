del EditorStable\ArgumentEditor.exe
robocopy bin/ EditorStable/ godot.windows.opt.tools.64.exe
rename EditorStable\godot.windows.opt.tools.64.exe "ArgumentEditor.exe"

git checkout master
git pull
git commit -a -m "[skip ci] Submitting stable editor"
git push origin