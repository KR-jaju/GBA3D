
#ifndef GAME_SYSTEM_HPP
# define GAME_SYSTEM_HPP

# include "Camera.hpp"

namespace GameSystem {
	void	update();
	void	main();

	Camera	camera;

	void	main() {
		
		while (true) {
			update();
		}
	}
	void	update() {
		// camera.push()
		camera.render((u8 *)0x06000000);
	}
}

#endif
