#include <graphx.h>
#include <keypadc.h>
#include <stdio.h>
#include <math.h>

#define LEN(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))

void begin(void);
void end(void);
bool step(void);
void draw(void);

int vectorsSize = 8;
double vectors[8][3] = {{50,50,50},{50,-50,50},{-50,-50,50},{-50,50,50},{50,50,-50},{50,-50,-50},{-50,-50,-50},{-50,50,-50}};
int vectorDisplay[8][3] = {{50,50,50},{50,-50,50},{-50,-50,50},{-50,50,50},{50,50,-50},{50,-50,-50},{-50,-50,-50},{-50,50,-50}};
int lineConnectionsSize = 12;
int lineConnections[12][2] = {{0,1},{1,2},{2,3},{3,0},{4,5},{5,6},{6,7},{7,4},{0,4},{1,5},{2,6},{3,7}};
double colors[8] = {10, 30, 50, 70, 90, 110, 130, 150};
double rotation[3] = {0,0,0};
int cameraDist = 2;
int width = 320; //screen size
int height = 240; //screen size

int main(void) {

    bool flag = true;

    begin();
    gfx_Begin();
    gfx_FillScreen(181);
    gfx_SwapDraw();
    gfx_FillScreen(181);
    gfx_SetTextFGColor(0);

    //main loop
    while (flag) {

        //do calculations here

        draw();
        gfx_SwapDraw();
        if (kb_Data[7] & kb_Left) {
            rotation[1] += 0.0872665;
        }
        if (kb_Data[7] & kb_Right) {
            rotation[1] -= 0.0872665;
        }
        if (kb_Data[7] & kb_Up) {
            rotation[0] -= 0.0872665;
        }
        if (kb_Data[7] & kb_Down) {
            rotation[0] += 0.0872665;
        }
        if (kb_Data[4] & kb_Cos) {
            rotation[0] -= 0.0872665;
        }
        if (kb_Data[5] & kb_Tan) {
            rotation[0] += 0.0872665;
        }
        if (kb_Data[6] & kb_Clear) { //exit condition
            flag = false;
        }
    }
    gfx_End();
    end();
    return 0;
}

void draw(void) { //draw to the screen
    gfx_SetColor(181);
    for (int i = 0; i < lineConnectionsSize; i++) {
        gfx_Line(vectorDisplay[lineConnections[i][0]][0], vectorDisplay[lineConnections[i][0]][1], vectorDisplay[lineConnections[i][1]][0], vectorDisplay[lineConnections[i][1]][1]);
        if (i < vectorsSize)
            gfx_FillCircle(vectorDisplay[i][0], vectorDisplay[i][1], 3);
    }
    
    for (int i = 0; i < vectorsSize; i++) {
        double xpos = vectors[i][0];
        double ypos = vectors[i][1];
        double zpos = vectors[i][2];

        double newX = xpos * cos(rotation[2]) - ypos * sin(rotation[2]);
        ypos = xpos * sin(rotation[2]) + ypos * cos(rotation[2]);
        xpos = newX;
        newX = xpos * cos(rotation[1]) + zpos * sin(rotation[1]);
        double newZ = -xpos * sin(rotation[1]) + zpos * cos(rotation[1]);
        xpos = newX;
        zpos = newZ;
        double newY = ypos * cos(rotation[0]) - zpos * sin(rotation[0]);
        zpos = ypos * sin(rotation[0]) + zpos * cos(rotation[0]);
        ypos = newY;

        int xOffset = (xpos / abs((int) xpos) * zpos / -abs((int) zpos)) * cameraDist;
        int yOffset = (ypos / abs((int) ypos) * zpos / -abs((int) zpos)) * cameraDist;

        vectorDisplay[i][0] = (int) xpos + width / 2 + xOffset;
        vectorDisplay[i][1] = (int) ypos + height / 2 + yOffset;
        vectorDisplay[i][2] = (int) zpos;
    }
    
    gfx_SetColor(224);
    for (int i = 0; i < lineConnectionsSize; i++) {
        gfx_Line(vectorDisplay[lineConnections[i][0]][0], vectorDisplay[lineConnections[i][0]][1], vectorDisplay[lineConnections[i][1]][0], vectorDisplay[lineConnections[i][1]][1]);
    }

    for(int i = 0; i < vectorsSize; i++) {
        gfx_SetColor(i);
        gfx_FillCircle(vectorDisplay[i][0], vectorDisplay[i][1], 3);
    }
    
    gfx_PrintStringXY("Xr: ", 1, 1);
    gfx_PrintInt((int) rotation[0], 1);
    gfx_PrintStringXY("Yr: ", 1, 10);
    gfx_PrintInt((int) rotation[1], 1);
    gfx_PrintStringXY("Zr: ", 1, 20);
    gfx_PrintInt((int) rotation[2], 1);
}

void begin(void) {
    //Load data and the such
}

void end(void) {
    //Save data and the such
}