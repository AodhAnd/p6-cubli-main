# Meeting 18/02

## Study regulations
Take these regulations as a whole: the general goal is to be able to set a model, evaluate it, simulate it, analyze it, design a contoller with different methods (root locus, etc.), ...

## Model
The rotational acceleration of the wheel should also account for the rest of the forces (torques) affecting the wheel.
The bearing of the wheel also applies some unpredictable force which affects the total movement of the wheel and can be drawn as we want.

Take a global coordinate system to have a good overview: it should be easier to combine the equations. When we reach the equations from the paper, we can also do it another way with respective (local) coordinate sytem and then use cross products to put back the two equations in the same coordinate system.

Do the model the "book way" :
1. Free-body diagrams
2. Put up all the forces applying on the system
3. Describe it with equations

Also possible later if we have time: use Lagrange method using energies, it can be elegant.

## Sensors
It is fine to try to use the IMUs, it should be possible to also use some parameters inside the code to run an observer and bypass the pot-meter.

## Code implementation process
A lot of code to go through but we should stay on the top layer not to loose time.

## Parameters
The approach of using the given parameters and verifying them later when we have made the controller up and running might be better since the point of this semester is the Control Engineering.


## Next meeting
On Monday 29th at 13.00