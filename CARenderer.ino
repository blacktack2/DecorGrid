#include "CARenderer.h"

#define NEIGHBOUR(x, y, dx, dy)\
mCells[(x == 0 && dx == -1) ? mGrid.getWidth()  - 1 : ((x == mGrid.getWidth()  - 1 && dx == 1) ? 0 : x + dx) +\
       (y == 0 && dy == -1) ? mGrid.getHeight() - 1 : ((y == mGrid.getHeight() - 1 && dy == 1) ? 0 : y + dy) * mGrid.getWidth()]

CARenderer::CARenderer(LEDGrid& grid) : Renderer(grid) {
  mCells = new cell[grid.getWidth() * grid.getHeight()];
  mNumGenerations = 1;
  mBirthRules = 1 << 3;
  mDeathRules = ~(1 << 2 | 1 << 3) & ((1 << 10) - 1);
  for (cell y = 0; y < mGrid.getHeight(); y++) {
    for (cell x = 0; x < mGrid.getWidth(); x++) {
      size_t index = x + y * mGrid.getWidth();
      mCells[index] = rand() & 1 ? mNumGenerations : 0;
      mGrid.setRGB(x, y, mCells[index] == 0 ? 0 : 100, 0, 0);
    }
  }
}

CARenderer::~CARenderer() {
  delete[] mCells;
}

void CARenderer::updateGrid() {
  cell* cells2 = new cell[mGrid.getWidth() * mGrid.getHeight()];
  for (cell y = 0; y < mGrid.getHeight(); y++) {
    for (cell x = 0; x < mGrid.getWidth(); x++) {
      unsigned int numNeighbours =
        NEIGHBOUR(x, y,  1,  1) +
        NEIGHBOUR(x, y,  0,  1) +
        NEIGHBOUR(x, y, -1,  1) +
        NEIGHBOUR(x, y,  1,  0) +
        NEIGHBOUR(x, y, -1,  0) +
        NEIGHBOUR(x, y, -1, -1) +
        NEIGHBOUR(x, y,  0, -1) +
        NEIGHBOUR(x, y, -1, -1);
      size_t index = x + y * mGrid.getWidth();
      cell current = mCells[index];
      cells2[index] = (current == 0 ? (mBirthRules & (1 << numNeighbours) ? mNumGenerations : current) : (current != mNumGenerations || mDeathRules & (1 << numNeighbours)) ? current - 1 : current);
      mGrid.setRGB(x, y, cells2[index] == 0 ? 0 : 100, 0, 0);
    }
  }
  delete[] mCells;
  mCells = cells2;
}
