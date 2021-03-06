#include "Dino.h"

Dino::Dino(SFGE::Window& l_window){
	jumping = false;
	grounded = true;
	l_window.GetEventManager()->AddCallback("Jump", &Dino::Jump, this);
	l_window.GetEventManager()->AddCallback("Duck", &Dino::Duck, this);
	vel = sf::Vector2f(0, 0);
	gravity = 30.0f;
	dead = false;
	animState = AnimState::RUNNING;
	sf::FloatRect b = body.getGlobalBounds();
	boundingBox = sf::FloatRect(b.left, b.top + 4, b.width - 2, b.height - 12);
}

void Dino::Draw(SFGE::Window& l_window){
	l_window.Draw(body);
	sf::RectangleShape r(sf::Vector2f(boundingBox.width, boundingBox.height));
	r.setPosition(body.getPosition().x, body.getPosition().y + (boundingBox.top - body.getGlobalBounds().top));
	r.setFillColor(sf::Color::Transparent);
	r.setOutlineThickness(1);
	r.setOutlineColor(sf::Color::Red);
	//l_window.Draw(r);
}

void Dino::Update(float dt, std::vector<Cactus>l_cacti, std::vector<Bird> l_birds){

	if (dead == true){
		vel.x = 0;
		vel.y = 0;
	}

	body.move(vel * dt);
	sf::FloatRect b = body.getGlobalBounds();
	switch (animState)
	{
	case AnimState::RUNNING:
		if (animClock.getElapsedTime().asSeconds() > timeBetweenFrames){
			if (currentFrame == 2){
				currentFrame = 0;
			}
			else{
				currentFrame++;
			}
			body.setTextureRect(sf::IntRect(44 * currentFrame, 0, 44, 54));
			animClock.restart();
		}

		boundingBox = sf::FloatRect(b.left, b.top + 4, b.width - 2, b.height - 12);
		break;
	case AnimState::JUMPING:
		body.setTextureRect(sf::IntRect(0, 0, 44, 54));
		boundingBox = sf::FloatRect(b.left, b.top + 4, b.width - 2, b.height - 12);
		break;
	case AnimState::DUCKING:
		if (animClock.getElapsedTime().asSeconds() > timeBetweenFrames){
			if (currentFrame == 1 || currentFrame == 2){
				currentFrame = 0;
			}
			else{
				currentFrame++;
			}
			body.setTextureRect(sf::IntRect((59 * currentFrame) + 132, 0, 59, 54));
			animClock.restart();
		}
		boundingBox = sf::FloatRect(b.left, b.top + 20, b.width - 2, b.height - 25);
		break;
	default:
		break;
	}


	if (body.getPosition().y < 164){
		animState = AnimState::JUMPING;
		vel.y += gravity;
	}
	else{
		animState = AnimState::RUNNING;
		body.setPosition(body.getPosition().x, 164);
	}

	for (Cactus cactus : l_cacti){
		sf::FloatRect bb = cactus.body.getGlobalBounds();
		if (boundingBox.intersects(sf::FloatRect(bb.left + 10, bb.top + 10, bb.width - 20, bb.height - 10))){
			dead = true;
			deathClock.restart();
		}
	}

	for (Bird bird : l_birds){
		sf::FloatRect bb = bird.body.getGlobalBounds();
		if (boundingBox.intersects(bird.boundingBox)){
			dead = true;
			deathClock.restart();
		}
	}
	gravity = 30.0f;
}

void Dino::SetTexture(sf::Texture& l_texture){
	body.setTexture(l_texture);
	body.setTextureRect(sf::IntRect(0, 0, 44, 54));
	animClock.restart();
	currentFrame = 0;
}

void Dino::Jump(SFGE::EventDetails* details){
	//std::cout << details->m_keyCode << "\n";
	if (body.getPosition().y >= 164){
		vel.y = -500;
	}
}

void Dino::Duck(SFGE::EventDetails* details){
	gravity = 100.0f;
	animState = AnimState::DUCKING;

}