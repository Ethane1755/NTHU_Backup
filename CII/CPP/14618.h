#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <iostream>

class Scene {
    public:
        Scene(int n, int m);
        ~Scene();
        int**& getGrid() { return grid; }
        void update(int m);
        void checkBlock();
        bool checkRow(int r) const;
        void eliminate(int r);
        void print() const;

    private:
        int row;
        int col;
        int gameTimer = 1;
        int** grid;
};

class Tetrominoes {
    public:
        Tetrominoes(int x, int y, int label) : x(x), y(y), label(label) {}
        virtual ~Tetrominoes() {}
        virtual void draw(int**& grid) = 0;

    protected:
        int x, y, label;
};

class IBlock : public Tetrominoes {
    public:
        IBlock(int x, int y, int label) : Tetrominoes(x, y, label) {}
        void draw(int**& grid) override;
};

class JBlock : public Tetrominoes {
    public:
        JBlock(int x, int y, int label) : Tetrominoes(x, y, label) {}
    void draw(int**& grid) override;
};

class LBlock : public Tetrominoes {
    public:
        LBlock(int x, int y, int label) : Tetrominoes(x, y, label) {}
        void draw(int**& grid) override;
};

class SBlock : public Tetrominoes {
    public:
        SBlock(int x, int y, int label) : Tetrominoes(x, y, label) {}
        void draw(int**& grid) override;
};

class TBlock : public Tetrominoes {
    public:
        TBlock(int x, int y, int label) : Tetrominoes(x, y, label) {}
        void draw(int**& grid) override;
};

class OBlock : public Tetrominoes {
    public:
        OBlock(int x, int y, int label) : Tetrominoes(x, y, label) {}
        void draw(int**& grid) override;
};

#endif

// You might start with the following codes:

/*
#include "function.h"

void IBlock::draw(int**& grid) {
    // ...
}

void JBlock::draw(int**& grid) {
    // ...
}

void LBlock::draw(int**& grid) {
    // ...
}

void SBlock::draw(int**& grid) {
    // ...
}

void TBlock::draw(int**& grid) {
    // ...
}

void OBlock::draw(int**& grid) {
    // ...
}

Scene::Scene(int n, int m) : row(n), col(m) {
    // ...
}

Scene::~Scene() {
    // ...
}

void Scene::update(int m) {
    // ...
}

void Scene::checkBlock() {
    // ...
}

bool Scene::checkRow(int r) const {
    // ...
}

void Scene::eliminate(int r) {
    // ...
}

void Scene::print() const {
    // ...
}
*/