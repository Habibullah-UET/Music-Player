
echo "[1]: Compiling Player.c "
gcc Player.c -o Player -lpulse-simple -lpulse
echo "[2]: done! "

echo "[3]: Setting Permission "
chmod 777 Player
echo "[4]: Executeable Copied to /bin"

 cp  Player /bin