% Bill Calabro
% RBE 501
% Project Velocity Kinematics
% 31614

close all
clear all
clc

format ('short');

% -- begin Inverse Velocity formulation --

% Inverse Position
% input X, Y, Z (values)
% output A, B, C (values)
% use existing C-code


% Forward Position Equations for Jacobian
% input A, B, C
% output Xeq, Yeq, Zeq
syms A B C;


drad = 175.00 - 40.32; %mm
% syms drad;
sin60 = 0.866;
cos60 = 0.5;


x2 = -1 * sin60 * drad;
x3 = sin60 * drad;

y1 = drad;
y2 = -1 * cos60 * drad;
y3 = -1 * cos60 * drad;

z1 = A;
z2 = B;
z3 = C;

re = 203.82; %mm
% syms re;

dnm = (x3 * (y2 - y1)) - (x2 * (y3 - y1));

w1 = y1^2 + z1^2;
w2 = x2^2 + y2^2 + z2^2;
w3 = x3^2 + y3^2 + z3^2;

a1 = ((z2 - z1) * (y3 - y1)) - ((z3 - z1) * (y2 - y1));
a2 = (x3 * (z2 - z1) * -1) + (x2 * (z3 - z1));

b1 = (((w2 - w1) * (y3 - y1)) - ((w3 - w1) * (y2 - y1))) * -1 * 0.5;
b2 = ((x3 * (w2 - w1)) - (x2 * (w3 - w1))) * 0.5;

a = a1^2 + a2^2 + dnm^2;
b = ((a1 * b1) + (a2 * (b2 - (y1 * dnm))) - (z1 * dnm^2)) * 2;
c = (b2 - (y1 * dnm))^2 + b1^2 + (dnm^2 * (z1^2 - re^2));
d = b^2 - (4 * a * c);

Zeq = ((b + sqrt(d)) / a) * -1 * 0.5;
Xeq = ((a1 * Zeq) + b1) / dnm;
Yeq = ((a2 * Zeq) + b2) / dnm;


% Jacobian
% input A, B, C and Xeq, Yeq, Zeq
% output J
J11 = diff(Xeq, A);
J12 = diff(Xeq, B);
J13 = diff(Xeq, C);

J21 = diff(Yeq, A);
J22 = diff(Yeq, B);
J23 = diff(Yeq, C);

J31 = diff(Zeq, A);
J32 = diff(Zeq, B);
J33 = diff(Zeq, C);

J = [J11 J12 J13; J21 J22 J23; J31 J32 J33];

% Print Jacobian pieces
% disp('J11');
% simplify(J11)
% disp('J12');
% simplify(J12)
% disp('J13');
% simplify(J13)
% disp('J21');
% simplify(J21)
% disp('J22');
% simplify(J22)
% disp('J23');
% simplify(J23)
% disp('J31');
% simplify(J31)
% disp('J32');
% simplify(J32)
% disp('J33');
% simplify(J33)


$ Output Jacobian to C Code
ccode(J, 'file', 'jacobianOutput');


% Inverse Velocity
% input J and Xd, Yd, Zd
% output Ad, Bd, Cd

% syms Xd Yd Zd;
% syms Ad Bd Cd;
% 
% jointDot = [Ad; Bd; Cd];
% taskDot = [Xd; Yd; Zd];
% 
% jointDot = (J' * inv(J * J'))  taskDot; %removed to improve code performance

% -- end formulation --


% Inverse Velocity Kinematics Useage in C-code

% input tool position (X, Y, Z), desired tool velocity (Xd, Yd, Zd)
% calculate current joint position (A, B, C) through existing Inverse Position function
% calculate Jacobian (J) using predefined formulas () of joint positions (A, B, C)
% calculate joint velocities (Ad, Bd, Cd) using Jacobian (J) and desired tool velocities (Xd, Yd, Zd)
% output joint velocities (Ad, Bd, Cd)


% Position Examples (as check of Matlab code)
jointEx = [160 180 180] %mm
taskExZ = subs(Zeq, [A, B, C], jointEx);
taskExX = subs(Xeq, [A, B, C], jointEx);
taskExY = subs(Yeq, [A, B, C], jointEx);
taskEx = [taskExX; taskExY; taskExZ] %mm


% Velocity Examples
taskVelEx1 = [100; 0; 0] %mm/s
JeX1 = subs(J, [A, B, C], [153, 153, 153]);
JeXInv1 = (JeX1' * inv(JeX1 * JeX1'));
jointVelEx1 = JeXInv1 * taskVelEx1 %mm/s

taskVelEx2 = [0; 100; 0] %mm/s
JeX2 = subs(J, [A, B, C], [153, 153, 153]);
JeXInv2 = (JeX2' * inv(JeX2 * JeX2'));
jointVelEx2 = JeXInv2 * taskVelEx2 %mm/s
