#include "../../include/gameplay/game.h"


Game::Game(ScoreData& sharedScoreData, TimeData& sharedTimeData) :
    m_scene(),
    m_state(GameplayState::Waiting),
    m_scoreData(sharedScoreData),
    m_timeData(sharedTimeData),
    m_scoreManager(&m_scoreData, 50, "assets/fonts/Ghrathe.ttf", Vector2f(50, 300)),
    m_timeManager(&m_timeData, 50, "assets/fonts/Ghrathe.ttf", Vector2f(50, 100)),
    m_inputManager(),

    m_boardTexture("assets/sprites/board/0.png"),
    m_itemTexture("assets/sprites/fruit/0.png"),

    m_board(m_boardTexture, 32.f),
    m_snake(Snake(m_board, Vector2f(6, 8))),
    m_fruit(m_itemTexture, Vector2f(m_board.getPosition().x + m_board.getCellSize()*12-16, m_board.getPosition().y + m_board.getCellSize()*8-16 )),

    m_background(Sprite("assets/sprites/background/0.png")),
    

    m_timer(),
    m_time(0.f),
    m_score(0)
{
    std::cout << "Game Initialisée" << std::endl;
}

Game::~Game()
{
    std::cout << "Game supprimée" << std::endl;
}

void Game::reset()
{

    m_state = GameplayState::play;
    m_score = 0;
    m_timer.reset();

    updateScore();
    updateTime();
    // réinitialiser l'm_inputManager

    m_snake.reset();
    m_fruit.reset();
}


void Game::Draw()
{
    m_scene.Use();
    
    m_scene.Draw(m_background);
    m_scene.Draw(m_board);
    m_scene.Draw(m_scoreManager);
    m_scene.Draw(m_timeManager);
    m_scene.Draw(m_fruit);
    m_scene.Draw(m_snake);

    m_scene.render();
}

void Game::update(GLFWwindow * window, float deltaTime)
{
    m_inputManager.update(window);

    if (m_state == GameplayState::Waiting && (m_inputManager.getInput().x != 0 || m_inputManager.getInput().y != 0)) {
        m_timer.reset();
        m_state = GameplayState::play;
    }
    if (m_state == GameplayState::play) {
        updateTime();
        updateSnake(deltaTime);
    }
}

void Game::updateScore()
{
    m_scoreData.setLastScore(m_score);
    m_scoreData.updateBestScore();
    m_scoreData.updateTotalScore();
    m_scoreManager.refreshFromData();
}

void Game::updateTime()
{
    m_time = m_timer.elapsed();
    m_timeData.setLastTime(m_time);
    m_timeData.updateBestTime();
    m_timeManager.refreshFromData();
}

void Game::updateSnake(float deltaTime)
{
    m_snake.update(m_inputManager.getInput(), deltaTime);

    if (m_snake.collideFruit(m_fruit.getPosition())) {
        m_snake.addSegment();
        m_score++;
        updateScore();
        moveItem();
    }
        
    if (m_snake.isDead(m_board.getPosition().x, m_board.getPosition().y)) {
        handleGameplayOver();
    }
}

void Game::moveItem()
{
    m_fruit.setPosition(m_board.getPosition(), m_board.getCellSize());
}

GameplayState Game::getState()
{
    return m_state;
}

void Game::handleGameplayOver()
{
    m_state = GameplayState::GameOver;
    std::cout << "Vous êtes mort" << std::endl;
}