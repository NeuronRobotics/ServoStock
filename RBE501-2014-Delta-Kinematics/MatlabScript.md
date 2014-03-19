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

% -- begin Inverse Velocity formulation --

% Inverse Position
% input: X, Y, Z (values)
% output: A, B, C (values)
% use existing C-code


% Forward Position Equations for Jacobian
% input: A, B, C
% output: Xeq, Yeq, Zeq
syms A B C;


% drad = 175.00 - 40.32;
syms drad;


x2 = -sin(pi/3) * drad;
x3 = sin(pi/3) * drad;

y1 = drad;
y2 = -cos(pi/3) * drad;
y3 = -cos(pi/3) * drad;

z1 = A;
z2 = B;
z3 = C;

% re = 203.82;
syms re;

dnm = (x3 * (y2 - y1)) - (x2 * (y3 - y1));

w1 = y1^2 + z1^2;
w2 = x2^2 + y2^2 + z2^2;
w3 = x3^2 + y3^2 + z3^2;

a1 = ((z2 - z1) * (y3 - y1)) - ((z3 - z1) * (y2 - y1));
a2 = (x3 * (z2 - z1) * -1) - (x2 * (z3 - z1));

b1 = (((w2 - w1) * (y3 - y1)) - ((w3 - w1) * (y2 - y1))) * -0.5;
b2 = ((x3 * (w2 - w1)) - (x2 * (w3 - w1))) * 0.5;

a = a1^2 + a2^2 + dnm^2;
b = ((a1 * b1) + (a2 * (b2 - (y1 * dnm))) - (z1 * dnm^2)) * 2;
c = (b2 - (y1 * dnm))^2 + b1^2 + (dnm^2 * (z1^2 - re^2));
d = b^2 - (4 * a * c);

Zeq = ((b + sqrt(d)) / a) * -0.5;
Xeq = ((a1 * Z) + b1) / dnm;
Yeq = ((a2 * Z) + b2) / dnm;


% Jacobian
% input: A, B, C and Xeq, Yeq, Zeq
% output: J
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


% Inverse Velocity
% input: J and Xd, Yd, Zd
% output: Ad, Bd, Cd

syms Xd Yd Zd;
syms Ad Bd Cd;

jointDot = [Ad; Bd; Cd];
taskDot = [Xd; Yd; Zd];

jointDot = (J' * inv(J * J')) * taskDot;

% -- end formulation --


% Inverse Velocity Kinematics Useage in C-code

% input: tool position (X, Y, Z), desired tool velocity (Xd, Yd, Zd)
% calculate current joint position (A, B, C) through existing Inverse Position function
% calculate Jacobian (J) using predefined formulas (?) of joint positions (A, B, C)
% calculate joint velocities (Ad, Bd, Cd) using Jacobian (J) and desired tool velocities (Xd, Yd, Zd)
% output: joint velocities (Ad, Bd, Cd)


% Position Example (as check of Matlab code)
jointEx = [153 153 153];
taskExZ = subs(Z, [A, B, C], jointEx);
taskExX = subs(X, [A, B, C], jointEx);
taskExY = subs(Y, [A, B, C], jointEx);
taskEx = [taskExX; taskExY; taskExZ];


% Velocity Example
taskVelEx = [10; 0; 0]
JeX = subs(J, [A, B, C], taskEx');
JeXInv = (JeX' * inv(JeX * JeX'));
jointVelEx = JeXInv * taskVelEx

