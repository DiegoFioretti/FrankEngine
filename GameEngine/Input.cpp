#include "Input.h"
#include <GLFW\glfw3.h>




Input::Input(Window* window)
{
	win = window;
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glfwSetMouseButtonCallback(window, mouse_button_callback);
}

// que key queres saber si se toca, 0 es siempre 1 es una sola vez
bool Input::keyCall(int key, int num) {

	//-------------LETRAS---------------------------
	int a = 0;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_Q) == GLFW_PRESS) {
		if (key == 'q') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_Q) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
		if (key == 'w') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_W) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_E) == GLFW_PRESS) {
		if (key == 'e') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_E) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_R) == GLFW_PRESS) {
		if (key == 'r') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_R) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_T) == GLFW_PRESS) {
		if (key == 't') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_T) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_Y) == GLFW_PRESS) {
		if (key == 'y') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_Y) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_U) == GLFW_PRESS) {
		if (key == 'u') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_U) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_I) == GLFW_PRESS) {
		if (key == 'i') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_I) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_O) == GLFW_PRESS) {
		if (key == 'o') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_O) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_P) == GLFW_PRESS) {
		if (key == 'p') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_P) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		if (key == 'a') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_A) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		if (key == 's') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_S) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		if (key == 'd') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_D) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_F) == GLFW_PRESS) {
		if (key == 'f') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_F) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_G) == GLFW_PRESS) {
		if (key == 'g') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_G) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_H) == GLFW_PRESS) {
		if (key == 'h') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_H) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_J) == GLFW_PRESS) {
		if (key == 'j') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_J) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_K) == GLFW_PRESS) {
		if (key == 'k') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_K) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_L) == GLFW_PRESS) {
		if (key == 'e') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_L) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_Z) == GLFW_PRESS) {
		if (key == 'z') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_Z) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_X) == GLFW_PRESS) {
		if (key == 'x') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_X) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_C) == GLFW_PRESS) {
		if (key == 'c') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_C) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_V) == GLFW_PRESS) {
		if (key == 'v') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_V) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_B) == GLFW_PRESS) {
		if (key == 'b') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_B) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_N) == GLFW_PRESS) {
		if (key == 'b') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_B) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_N) == GLFW_PRESS) {
		if (key == 'n') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_N) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_M) == GLFW_PRESS) {
		if (key == 'm') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_M) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;
	//numpad

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_8) == GLFW_PRESS) {
		if (key == '8') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_8) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_4) == GLFW_PRESS) {
		if (key == '4') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_4) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_6) == GLFW_PRESS) {
		if (key == '6') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_6) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_2) == GLFW_PRESS) {
		if (key == '2') {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_2) == GLFW_RELEASE) {
		keyReleased[a] = true;
	}
	a++;
	return false;
}

bool Input::keyCall(string key, int num) {
	int a = 0;

	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS){
		if (key == "Space") {
			switch (num) {
			case 0:
				return true;
				break;
			case 1:
				if (keyReleased[a]) {
					keyReleased[a] = false;
					return true;
				}
				break;

			default:
				break;
			}
		}
	}
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), GLFW_KEY_SPACE) == GLFW_RELEASE ) {
		keyReleased[a] = true;
	}
	a++;

	return false;
}

