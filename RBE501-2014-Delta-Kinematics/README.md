https://help.github.com/articles/github-flavored-markdown 

Forward/Inverse Velocity Technique:
1) Forward Velocity: Derived in the MatlabScript.md file. The technique used to derive the forward velocity for the Delta Robot was to
take the Jacobian of the Position Kinematics in order to create a Jacobian matrix that aids in deriving the forward velocity of the end effector. More details of this technique can be found in the MatlabScript.md file.

2) Inverse Velocity Technique: Derived in MatlabScript.md file. Since the Jacobian was used to determine the forward velocity of the Delta Robot, the Inverse Velocity was a straight forward technique known as the Derivation of the Pseudoinverse (Moore-Penrose Inverse). The reason this technique was used as opposed to simply taking the inverse of the Jacobian and multiplying by the velocity matrix of the end effector is because in our case we had a greater number of rows than columns (e.g. n>m) in our matrix. More details of this technique can be found in the MatlabScript.md file.


Manual Test Procedures:
Forward Position Kinematics Test Case:
1) Using the following equations:
Acz = sqrt(L^2 - (X - Avx)^2 - (Y - Avy)^2)
Bcz = sqrt(L^2 - (X - Bvx)^2 - (Y - Bvy)^2)
Ccz = sqrt(L^2 - (X - Cvx)^2 - (Y – Cvy)^2)
Select a desired end effector X and Y position and calculate the carriage height values above the effector platform.
2) Using the following equations:
Az = Z + Acz + Hcz
Bz = Z + Bcz + Hcz
Cz = Z + Ccz + Hcz

Calculate the values for Az, Bz, and Cz, the Z components of the carriage positions, using the carriage height values from 1) and using the constant values Z and Hcz, the height of the head above the bed and the distance the head extends below the carrier, respectively.
3) Using the Delta Kinematics software, input the carriage positions calculated in 2) and verify the software moves to the desired X and Y position chosen in 1)

Inverse Position Kinematics Test Case:
1) Using the following equations:
Acz = Az - Z - Hcz
Bcz = Bz - Z – Hcz
Ccz = Cz - Z – Hcz

a. Select a desired Az, Bz, and Cz, the Z components of the carriage positions.
b. Solve for Acz, Bcz, and Ccz using the selected carriage positions from 1)b. and using the constant values Z and Hcz, the height of the head above the bed and the distance the head extends below the carrier, respectively.

2) Using the following equations:
(X - Avx)^2 + (Y - Avy)^2 + Acz^2 = L^2
(X - Bvx)^2 + (Y - Bvy)^2 + Bcz^2 = L^2
(X - Cvx)^2 + (Y - Cvy)^2 + Ccz^2 = L^2
a) Solve for the X and Y positions using the calculated values from 1)c.

3) Using the Delta Kinematics software, input the calculated X and Y positions from 2)b. and verify software moves to the desired Az, Bz, and Cz (Z components of the carriage positions).
Forward Velocity Kinematics Test Case:
Note: Our team has not determined the velocity kinematics for the Delta Robot at this time.
1) Using the following equations:
TBD
Select a desired end effector X and Y velocity vector components and calculate the carriage height above the effector platform velocity values.
2) Using the following equations:
TBD

Calculate the Az, Bz, and Cz  Z velocity vector components of the carriage velocities
3) Using the Delta Kinematics software, input the carriage velocities calculated in 2) and verify the software moves at the end effector X and Y velocities selected in 1)
Inverse Velocity Kinematics Test Case:
Note: Our team has not determined the velocity kinematics for the Delta Robot at this time.
1) Using the following equations:
TBD

Select a desired Az, Bz, and Cz  Z velocity vector components of the carriage velocities.

2) Using the following equations:
TBD

Solve for the X and Y velocity vector components using the calculated values from 1).

3) Using the Delta Kinematics software, input the calculated X and Y velocity vector components from 2) and verify software moves to the a desired Az, Bz, and Cz  Z velocities selected in 1)
