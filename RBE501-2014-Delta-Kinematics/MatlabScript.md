/*
 ============================================================================
 Name        : MatlabScript.md
 Author      : Bill Calabro
 Version     :
 Copyright   : BSD with attribution
 Description : Matlab Script(s) used in project development and simulation
 ============================================================================
 */

% Bill Calabro
% RBE 501
% Project Velocity Kinematics
% 3/16/14

close all
clear all
clc

format ('short');

% Forward Kinematics
% input: A, B, C
% output: X, Y, Z
syms A B C;

drad = 175.00 - 40.32;

x2 = -sin(pi/3) * drad;
x3 = sin(pi/3) * drad;

y1 = drad;
y2 = -cos(pi/3) * drad;
y3 = -cos(pi/3) * drad;

z1 = A;
z2 = B;
z3 = A;

re = 203.82;

dnm = (x3 * (y2 - y1)) - (x2 * (y3 - y1));

w1 = y1^2 + z1^2;
w2 = x2^2 + y2^2 + z2^2;
w3 = x3^2 + y3^2 + z3^2;

a1 = ((z2 - z1) * (y3 - y1)) - ((z3 - z1) * (y2 - y1));
a2 = (x3 * (z2 - z1) * -1) - (x2 * (z3 - z1));

b1 = (((w2 - w1) * (y3 - y1)) - ((w3 - w1) * (y2 - y1))) * -0.5;
b2 = ((x3 * (w2 - w1) * -1) - (x2 * (w3 - w1))) * 0.5;

a = a1^2 + a2^2 + dnm^2;
b = ((a1 * b1) + (a2 * (b2 - (y1 * dnm))) - (z1 * dnm^2)) * 2;
c = (b2 - (y1 * dnm))^2 + b1^2 + (dnm^2 * (z1^2 - re^2));
d = b^2 - (4 * a * c);

Z = ((b + sqrt(d)) / a) * -0.5;
X = ((a1 * Z) + b1) / dnm;
Y = ((a2 * Z) + b2) / dnm;


% Position Example
jointEx = [153 153 153];
taskExZ = subs(Z, [A, B, C], jointEx);
taskExX = subs(X, [A, B, C], jointEx);
taskExY = subs(Y, [A, B, C], jointEx);
taskEx = [taskExX; taskExY; taskExZ];


% Jacobian
J11 = diff(X, A);
J12 = diff(X, B);
J13 = diff(X, C);

J21 = diff(Y, A);
J22 = diff(Y, B);
J23 = diff(Y, C);

J31 = diff(Z, A);
J32 = diff(Z, B);
J33 = diff(Z, C);

J = [J11 J12 J13; J21 J22 J23; J31 J32 J33];


% Velocity Kinematics
syms Xd Yd Zd;
syms Ad Bd Cd;

jointDot = [Ad; Bd; Cd];
taskDot = [Xd; Yd; Zd];

taskDotF = J * jointDot;
jointDotI = (J' * inv(J * J')) * taskDot;


% Velocity Example
taskVelEx = [10; 0; 0]
JeX = subs(J, [A, B, C], taskEx');
JeXInv = (JeX' * inv(JeX * JeX'));
jointVelEx = JeXInv * taskVelEx

