#include "noisegenerator.h"

void NoiseGenerator::run() {
    quint64 threadId = reinterpret_cast<quint64>(QThread::currentThreadId());
    QRandomGenerator generator(threadId + time(NULL));
    for (int y = startY; y < endY; y++) {
        for (int x = 0; x < width; x++) {
            int i = (y * width + x) * 4;
            uint rgb = generator.bounded(256);
            noiseData[i] = noiseData[i+1] = noiseData[i+2] = rgb;
            noiseData[i+3] = 255;
        }
    }
}
