void idle(Clock* clock){
	Vector2i position = Mouse::getPosition();
	timeStep = clock->restart().asMilliseconds();
	if(position.x < 100){
		x -= .3 * timeStep;
	}
	if(position.x > windowWidth - 100){
		x += .3 * timeStep;
	}
	if(position.y < 100){
		y += .3 * timeStep;
	}
	if(position.y > windowHeight - 100){
		y -= .3 * timeStep;
	}
}
