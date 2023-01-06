#include "CARenderer.h"

CARenderer::CARenderer(LEDGrid& grid) : Renderer(grid) {
  mCells = new cell[grid.getWidth() * grid.getHeight()];
  mNumGenerations = 1;
  mBirthRules = 1 << 1;
  mDeathRules = ~(0 << 0) & ((1 << 10) - 1);
  Serial.println(String("Birth: ") + String(mBirthRules));
  Serial.println(String("Death: ") + String(mDeathRules));
  for (cell y = 0; y < mGrid.getHeight(); y++) {
    for (cell x = 0; x < mGrid.getWidth(); x++) {
      size_t index = x + y * mGrid.getWidth();
      mCells[index] = 0;
    }
  }
  mCells[mGrid.getWidth() / 2 + mGrid.getHeight() * mGrid.getWidth() / 2] = mNumGenerations;
  if (!(mGrid.getWidth() & 1)) {
    mCells[mGrid.getWidth() / 2 - 1 + mGrid.getHeight() * mGrid.getWidth() / 2] = mNumGenerations;
    if (!(mGrid.getHeight() & 1)) {
      mCells[mGrid.getWidth() / 2 + (mGrid.getHeight() / 2 - 1) * mGrid.getWidth()] = mNumGenerations;
      mCells[mGrid.getWidth() / 2 - 1 + (mGrid.getHeight() / 2- 1) * mGrid.getWidth()] = mNumGenerations;
    }
  } else if (!(mGrid.getHeight() & 1)) {
    mCells[mGrid.getWidth() / 2 + (mGrid.getHeight() / 2 - 1) * mGrid.getWidth()] = mNumGenerations;
  }
}

CARenderer::~CARenderer() {
  delete[] mCells;
}

#define NEIGHBOUR(x, y, dx, dy)\
mCells[\
  ((x == 0 && dx == -1) ?\
    mGrid.getWidth()  - 1 :\
    ((x == mGrid.getWidth()  - 1 && dx == 1) ? 0 : x + dx)) +\
  ((y == 0 && dy == -1) ?\
    mGrid.getHeight() - 1 :\
    ((y == mGrid.getHeight() - 1 && dy == 1) ? 0 : y + dy)) * mGrid.getWidth()\
]

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
        NEIGHBOUR(x, y,  1, -1) +
        NEIGHBOUR(x, y,  0, -1) +
        NEIGHBOUR(x, y, -1, -1);
      size_t index = x + y * mGrid.getWidth();
      cell current = mCells[index];
      cells2[index] = (!current ? (mBirthRules & (1 << numNeighbours) ? mNumGenerations : current) : ((current != mNumGenerations || (mDeathRules & (1 << numNeighbours)))) ? current - 1 : current);
      color_channel_t c = (color_channel_t)((mCells[index] * 255) / mNumGenerations);
      mGrid.setHSV(x, y, 0, 255, c);
    }
  }
  delete[] mCells;
  mCells = cells2;
}
