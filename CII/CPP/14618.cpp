#include <iostream>
#include "14618.h"
using namespace std;

Scene::Scene(int n, int m) :row(n), col(m) {
    grid[row][col];
}

int main() {
    int n, t;
    cin >> n >> t;
    Scene scene(10, 15);

    for (int i = 1; i <= n; i++) {
        int m, p, x, y;
        cin >> m >> p >> x >> y;
        
        scene.update(m);

        if(p == 1) {
            IBlock block(x, y, i);
            block.draw(scene.getGrid());
        }
        else if(p == 2) {
            JBlock block(x, y, i);
            block.draw(scene.getGrid());
        }
        else if(p == 3) {
            LBlock block(x, y, i);
            block.draw(scene.getGrid());
        }
        else if(p == 4) {
            SBlock block(x, y, i);
            block.draw(scene.getGrid());
        }
        else if(p == 5) {
            TBlock block(x, y, i);
            block.draw(scene.getGrid());
        }
        else if(p == 6) {
            OBlock block(x, y, i);
            block.draw(scene.getGrid());
        }
        scene.checkBlock();
    }
    scene.update(t);
    scene.print();

    return 0;
}