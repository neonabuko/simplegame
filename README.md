<div align="center">
    <head>
        <link rel="preconnect" href="https://fonts.googleapis.com">
        <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
        <link href="https://fonts.googleapis.com/css2?family=Press+Start+2P&display=swap" rel="stylesheet">
    </head>
    <svg xmlns="http://www.w3.org/2000/svg" width="500" height="80">
      <text y="55" font-family="'Press Start 2P', cursive" font-size="45" fill="aliceblue">Simple Game</text>
    </svg><br><br>
    <img src="icon/player.png" alt="player" width="266" height="283.5">
    <img src="icon/enemy.png" alt="enemy" width="225.5" height="240.5">
</div>

<div>
    <svg xmlns="http://www.w3.org/2000/svg" width="500" height="80">
      <text y="80" font-family="'Press Start 2P', cursive" font-size="20" fill="aliceblue">Installing</text>
    </svg><br>

```shell
git clone https://github.com/neonabuko/simplegame

cd simplegame

cmake --build cmake-build-debug --target simplegame -j 10
```
<svg xmlns="http://www.w3.org/2000/svg" width="500" height="80">
      <text y="80" font-family="'Press Start 2P', cursive" font-size="20" fill="aliceblue">Running</text>
    </svg><br>

```shell
cd cmake-build-debug && ./simplegame
```
</div>