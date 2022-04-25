	std::cout << "\n--> Sprite class: Test rule of 5 started\n";
	{
		Sprite sprite1{ "Resources/RunningKnight.png", 8, 1, 0.08f }; 
		Sprite sprite2{ "Resources/RunningKnight.png", 8, 1, 0.08f }; 
		Sprite sprite3{ sprite1 }; 
		sprite2 = sprite1;
		Sprite sprite4{ CreateSprite("Resources/Tibo.png", 5, 5, 1 / 10.f) };  
		sprite1 = CreateSprite("Resources/Tibo.png", 5, 5, 1 / 10.f); 
		std::cout << "std::move: ";
		sprite2 = std::move(sprite1); 
	}
	std::cout << "--> Sprite class: Test rule of 5 ended\n";