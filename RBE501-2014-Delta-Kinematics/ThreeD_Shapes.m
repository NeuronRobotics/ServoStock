%% 3D Square Plotting

clear all; close all; clc;

%Open output coordinates text file
sid = fopen('data.txt', 'wt');

%Set this to the length of a side of desired square
sf = 1; %base square size scaling factor

%Set this to the height of the desired box
sZ = 2; %desired Z height for square box (minimum needs to be = zf or .1)

%Vertical Z variables
z0 = 0; %current incremented Z height
zf = 0.1; %z height factor (based on desired ink depth, default=0.1)
%To compute iterations, vertical height sZ = zf x zm
zm = round(sZ/zf); %number of vertical iterations needed

%Horizontal Y variables (X shares the Y variables)
y0 = 1*sf; %current incremented Y position
yf = 0.1; %y spacing factor (must be between 0.1 and 1(unfilled square))
sY = 2*sf; %y length
ym = round(sY/(yf*2)); %1/2 number of horizontal iterations needed

%Filled 2D Square
figure(1);
axis([-2*sf 2*sf -2*sf 2*sf 0 4*sf]);
title('3D Close Faced Box'); 
%fill3(X,Y,Z,2) %shades square area for better view

%2D to 3D Square Loop 
for i = 1:zm
    hold on;
    yold = y0; %these variables track the previous coordinates, only used for continuous MATLAB plotting
    zold = z0;
    X = [yold, y0, y0, -y0, -y0, y0];
    Y = [yold, y0, -y0, -y0, y0, y0];
    Z = [zold, z0, z0, z0, z0, z0];
    for i = 1:ym                    
        plot3(X,Y,Z); %<-- Send this array of coordinates to the printer        
        fprintf(sid, '%f %f %f \r\n', X(1),Y(1),Z(1)); %writes space separated coordinates to text file
        fprintf(sid, '%f %f %f \r\n', X(2),Y(2),Z(2));
        fprintf(sid, '%f %f %f \r\n', X(3),Y(3),Z(3));
        fprintf(sid, '%f %f %f \r\n', X(4),Y(4),Z(4));
        fprintf(sid, '%f %f %f \r\n', X(5),Y(5),Z(5));        
        yold = y0;
        y0 = y0 - yf; %decrement square diameter diagonally        
        X = [yold, y0, y0, -y0, -y0, y0];
        Y = [yold, y0, -y0, -y0, y0, y0];      
    end
    y0 = 1*sf; %reset y0
    z0 = z0 + zf; %increment height    
    hold off;
end

%Close out output text file
fclose(sid);

%% 3D Pyramid Plotting
% Warning: The base length, height, and slope must be carefully chosen to
% avoid extreme cases (very steep slope with short height, very narrow
% slope with short base), otherwise model fails.

clear all; close all; clc;

%Open output coordinates text file
pid = fopen('data.txt', 'wt');

%Set this to the length of a side of desired base square
sf = 1; %base square size scaling factor

%Set this to the angle of the sides
slp = 45; %slope of sides in degrees(must be between 0 to 90, set to 0 for square)

%Set this to the height of the desired pyramid
sZ = 2; %desired Z height for square box (minimum needs to be = zf or .1)

%Vertical Z variables
z0 = 0; %current incremented Z height
zf = 0.1; %z height factor (based on desired ink depth, default=0.1)
%To compute iterations, vertical height sZ = zf x zm
zm = round(sZ/zf); %number of vertical iterations needed

%Horizontal Y variables (X shares the Y variables)
y0 = 1*sf; %current incremented Y position
yf = 0.1; %y spacing factor (must be between 0.1 and 1(unfilled square))
sY = 2*sf; %y length
ym = round(sY/(yf*2)); %length decreases by twice scaling factor so half number of horizontal iterations needed

%Using law of sines to determine Y offset during each Z increment
% Based on the desired slope angle, the Y offset will be adjusted
% to create a decreasing square during each Z iteration so that 
% the shape of a pyramid emerges with evenly sloped sides
tAng = 90 - slp; %third angle of triangle
yOff = ((sZ/sin(tAng*pi/180))*sin(slp*pi/180))/zm; %calculate Y offset (zf/tAng = yOff/slp, law of sines)

%Filled 2D Square
figure(2);
axis([-2*sf 2*sf -2*sf 2*sf 0 4*sf]);
title('3D Pyramid'); 

%2D to 3D Square Loop 
for i = 1:zm
    hold on;    
    yold = y0; %these variables track the previous coordinates, only used for continuous MATLAB plotting
    zold = z0;
    X = [yold, y0, y0, -y0, -y0, y0];
    Y = [yold, y0, -y0, -y0, y0, y0];
    Z = [zold, z0, z0, z0, z0, z0];
    for j = 1:ym                    
        plot3(X,Y,Z); %<-- Send this array of coordinates to the printer
        fprintf(pid, '%f %f %f \r\n', X(1),Y(1),Z(1)); %writes space separated coordinates to text file
        fprintf(pid, '%f %f %f \r\n', X(2),Y(2),Z(2));
        fprintf(pid, '%f %f %f \r\n', X(3),Y(3),Z(3));
        fprintf(pid, '%f %f %f \r\n', X(4),Y(4),Z(4));
        fprintf(pid, '%f %f %f \r\n', X(5),Y(5),Z(5)); 
        yold = y0;
        y0 = y0 - yf; %decrement square diameter diagonally        
        X = [yold, y0, y0, -y0, -y0, y0];
        Y = [yold, y0, -y0, -y0, y0, y0];       
    end    
    y0 = (1*sf) - (yOff*i)/2; %reset y0 to new origin by subtracting half of offset  
    sY = (2*sf) - (yOff*i); %decrement to set new y length
    ym = round((sY/(yf*2))-0.5) %recalc y-loop & round down to avoid clipping
    z0 = z0 + zf %increment height    
    hold off;
end

%Close out output text file
fclose(pid);

%% 3D Cylinder Plotting

clear all; close all; clc;

%Open output coordinates text file
cid = fopen('data.txt', 'wt');

%Set this to the diameter of desired base circle
d = 2; %base circle size scaling factor

%Set this to the height of the desired pyramid
cZ = 2; %desired Z height for cylinder (minimum needs to be = zf or .1)

%Vertical Z variables
z0 = 0; %current incremented Z height
zf = 0.1; %z height factor (based on desired ink depth, default=0.1)
%To compute iterations, vertical height sZ = zf x zm
zm = round(cZ/zf); %number of vertical iterations needed

%Horizontal Y variables (X shares the Y variables)
x0 = 0; %current incremented X position
y0 = 0; %current incremented Y position
ys = 0.3; %y stepping factor (lower the better)
r = d/2; %radius
cir = 2*pi*r; %circumference
cAng = (2*pi)/(cir/ys); %slice up circle based on level of precision

%Filled 2D Square
figure(3);
axis([-d d -d d 0 2*cZ]);
title('3D Cylinder');

%2D to 3D Square Loop 
for i = 1:zm
    hold on;
    for j = 1:round(d/(2*ys)) %diameter size decreases by twice the stepping factor
        cir = 2*pi*r; %decrease circumference
        cAng = (2*pi)/(cir/ys); %slice up smaller circle based on level of precision
        xold = x0; %these variables track the previous coordinates, only used for continuous MATLAB plotting
        yold = y0;
        zold = z0;
        for k = 1:round((cir/ys))
            x0 = r * cos(cAng*k); %circle geometry
            y0 = r * sin(cAng*k); %circle geometry
            X = [xold,x0];
            Y = [yold,y0];
            Z = [zold,z0];
            plot3(X,Y,Z); %<-- Send this set of coordinates to the printer
            xold = x0;
            yold = y0;
            zold = z0;
            fprintf(cid, '%f %f %f \r\n', x0,y0,z0); %writes space separated coordinates to text file
        end
        r = (d/2) - (ys*j);        
    end
    r = d/2;
    z0 = z0 + zf; %increment height    
    hold off;
end

%Close out output text file
fclose(cid);