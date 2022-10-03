#pragma once
class Renderer
{
public:
	static Renderer* getInstance();
	static void initialize();
	static void destroy();
	
private:
	Renderer();
	~Renderer();
	
	Renderer(Renderer const&) {};
	Renderer& operator=(Renderer const&) {};
	static Renderer* sharedInstance;

};

