// #include <math.h>
// #include <unistd.h>
// #include "ssd1306.h"


// void drawPulsingBubble() {
//     int centerX = 64; // Middle of the screen
//     int centerY = 32;
//     int radius = 10; // Starting radius of the bubble
//     int frameDelay = 100000; // Delay in microseconds

//     for (int i = 0; i < 10; i++) { // Simple loop for animation
//         ssd1306_clear_screen(0x00); // Clear the screen
//         int currentRadius = radius + (sin(i * 0.5) * 10); // Calculate dynamic radius
//         ssd1306_draw_circle(centerX, centerY, currentRadius, 1); // Draw the bubble
//         ssd1306_refresh_gram(); // Refresh the screen to show the drawing
//         usleep(frameDelay); // Wait for the next frame
//     }
// }
