#pragma once
#include <string>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include "EventManager.h"
namespace SFGE{
	class Window
	{
	public:
		Window(std::string l_bindingsFilepath);
		Window(const std::string& l_title, const sf::Vector2u& l_size, std::string l_bindingsFilepath);
		~Window();

		void BeginDraw();//Clear the window
		void EndDraw();// Display the changes

		void Update();
		bool IsDone();
		bool IsFocused();
		bool IsFullscreen();
		void SetDone(bool done);
		sf::Vector2u GetWindowSize();
		sf::RenderWindow* GetRenderWindow(){ return &m_window; }
		void SetClearColor(sf::Color l_c){ m_clearColor = l_c; }
		sf::Color GetClearColor(){ return m_clearColor; }

		EventManager* GetEventManager() { return &m_eventManager; }
		void ToggleFullscreen(EventDetails* l_details);
		void Close(EventDetails* l_details = nullptr);

		void Draw(sf::Drawable& l_drawable);
		void Draw(sf::Drawable& l_drawable, sf::Shader& l_shader);


	private:
		void Setup(const std::string& l_title, const sf::Vector2u& l_size);
		void Destroy();
		void Create();

		sf::RenderWindow m_window;
		sf::Vector2u m_windowSize;
		std::string m_windowTitle;
		bool m_isDone;
		bool m_isFullscreen;
		bool m_isFocused;
		sf::Color m_clearColor;

		EventManager m_eventManager;

	};
}
