#include <graphx.h>
#include <keypadc.h>
#include <stdio.h>
#include <math.h>

void draw(void);

int vectorsSize = 8; //length of the vectors array
double vectors[8][3] = {{50,50,50},{50,-50,50},{-50,-50,50},{-50,50,50},{50,50,-50},{50,-50,-50},{-50,-50,-50},{-50,50,-50}}; //supplied coordinates to render
int vectorDisplay[8][3] = {{50,50,50},{50,-50,50},{-50,-50,50},{-50,50,50},{50,50,-50},{50,-50,-50},{-50,-50,-50},{-50,50,-50}}; //duplicate of the vectors array
int lineConnectionsSize = 12; //size of the lineConnections array
int lineConnections[12][2] = {{0,1},{1,2},{2,3},{3,0},{4,5},{5,6},{6,7},{7,4},{0,4},{1,5},{2,6},{3,7}}; //an array the contains info about which coordinates are connected by a line
double colors[8] = {10, 30, 50, 70, 90, 110, 130, 150}; //an array of colors to add variation to the display screen
double rotation[3] = {0,0,0}; //the rotation of the "screen"
int cameraDist = 2; //scale of the world, or how far the camera is from the origin
int width = 320; //screen width in pixels (or the area you want to render in)
int height = 240; //screen height in pixels (or the area you want to render in)

int main(void) { //main function

    bool flag = true; //exit flag. exit upon flag = false

    gfx_Begin(); //obvious
    gfx_FillScreen(181); //fill screen with grey
    gfx_SwapDraw(); //swap buffers
    gfx_FillScreen(181); //fill other buffer as well
    gfx_SetTextFGColor(0); //set text color to black, can be omitted

    //main loop
    while (flag) {

        //do other calculations here

        draw(); //main rendering function (also calculating cus im dumb)
        gfx_SwapDraw(); //swap buffers
        //*** check for mouse input ***
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
    gfx_End(); //end drawing
    return 0;
}

void draw(void) { //draw to the screen
    gfx_FillScreen(181); //clear screen
    
    for (int i = 0; i < vectorsSize; i++) { //loop thru all the points
        double xpos = vectors[i][0]; //get x coordinate of 3d point
        double ypos = vectors[i][1]; //get y coordinate of 3d point
        double zpos = vectors[i][2]; //get z coordinate of 3d point

        //*** APPLYING ROTATION MATRIX ***
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
        //*** FINISHED APPLIYING ROTATION MATRIX ***

        int xOffset = (xpos / abs((int) xpos) * zpos / -abs((int) zpos)) * cameraDist; //IGNORE THESE 2 LINES!! They were here to make a fake perspective
        int yOffset = (ypos / abs((int) ypos) * zpos / -abs((int) zpos)) * cameraDist; //effect bc i didn't know how to. You should learn it yourself instead.

        vectorDisplay[i][0] = (int) xpos + width / 2 + xOffset; //setting the display values
        vectorDisplay[i][1] = (int) ypos + height / 2 + yOffset;
        vectorDisplay[i][2] = (int) zpos;
    }
    
    gfx_SetColor(224);
    for (int i = 0; i < lineConnectionsSize; i++) { //a loop to display all the lines in order
        gfx_Line(vectorDisplay[lineConnections[i][0]][0], vectorDisplay[lineConnections[i][0]][1], vectorDisplay[lineConnections[i][1]][0], vectorDisplay[lineConnections[i][1]][1]);
    }

    for(int i = 0; i < vectorsSize; i++) { //a loop to display all the points
        gfx_SetColor(i);
        gfx_FillCircle(vectorDisplay[i][0], vectorDisplay[i][1], 3);
    }
    
    gfx_PrintStringXY("Xr: ", 1, 1); //dislplay rotations (as ints so it doesn't work)
    gfx_PrintInt((int) rotation[0], 1);
    gfx_PrintStringXY("Yr: ", 1, 10);
    gfx_PrintInt((int) rotation[1], 1);
    gfx_PrintStringXY("Zr: ", 1, 20);
    gfx_PrintInt((int) rotation[2], 1);
}
