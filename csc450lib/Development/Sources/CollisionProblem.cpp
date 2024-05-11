#include <CollisionProblem.h>

/**
 * CollisiomProblem constructor; consists of a ballistic
 * function and a surface.
 * 
 * @param ballistic the ballistic function
 * @param surface the surface
 * @return a CollisionProblem object
*/
CollisionProblem::CollisionProblem(BallisticFunction* ballistic, Surface* surface)
: ballistic(ballistic), surface(surface) {}

/**
 * Gets the object's height above the surface at time t.
 * 
 * @param t the time to get the difference at
 * @return the difference between the height of the surface
*/
float CollisionProblem::func(float t) const {
    std::vector<float> position = this->ballistic->getPosition(t);
    float surface_height = this->surface->func(position[0]);
    return position[1] - surface_height;
}