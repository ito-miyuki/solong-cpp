#include "solong.hpp"

int main()
{
    sf::Vector2i playerPos(0,0);
    sf::Vector2i enemyStartPos(0,0);

    int totalItems = 0;
    std::vector<std::vector<char>> map = read_map("map/map1.txt", playerPos, enemyStartPos, totalItems);

    int rows = map.size(); // マップの行数
    int cols = map[0].size(); // マップの列数

    Game game(totalItems, enemyStartPos);

    sf::RenderWindow window(sf::VideoMode(cols * tileSize, rows * tileSize), "My window");

    sf::Texture player_tex, floor_tex, grass_tex, item_tex, exit_tex, enermy_tex;
    sf::Sprite player_sprite = put_texture(player_tex, "png/player.png");
    sf::Sprite floor_sprite = put_texture(floor_tex, "png/floor.png");
    sf::Sprite grass_sprite = put_texture(grass_tex, "png/grass.png");
    sf::Sprite item_sprite = put_texture(item_tex, "png/onigiri.png");
    sf::Sprite exit_sprite = put_texture(exit_tex, "png/exit.png");
    sf::Sprite enermy_sprite = put_texture(enermy_tex, "png/enermy.png");

    while (window.isOpen())
    {
        // ウィンドウで発生したイベント（キーボード、マウス、ウィンドウの閉じるボタンなど）を処理
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            movement(playerPos, map, event, game);
        }
        
        if (game.checkGameOver(playerPos)) {
            game.update(window);
        } else {
            window.clear(sf::Color::Blue);
            game.moveEnemy(map);
        }

        for (int row = 0; row < map.size(); ++row) {
            for (int col = 0; col < map[row].size(); col++) {
                floor_sprite.setPosition((col * tileSize), row * tileSize);
                window.draw(floor_sprite);
                if (map[row][col] == '1') {
                    grass_sprite.setPosition(col * tileSize, row * tileSize);
                    window.draw(grass_sprite);
                }
                else if (map[row][col] == 'C') {
                    item_sprite.setPosition(col * tileSize, row * tileSize);
                    window.draw(item_sprite);
                }
                else if (map[row][col] == 'E') {
                    exit_sprite.setPosition(col * tileSize, row * tileSize);
                    window.draw(exit_sprite);
                }
                // else if (map[row][col] == 'X') {
                //     enermy_sprite.setPosition(col * tileSize, row * tileSize);
                //     window.draw(enermy_sprite);
                // }
            }
        }
        player_sprite.setPosition(playerPos.x * tileSize, playerPos.y * tileSize);
        window.draw(player_sprite);

        enermy_sprite.setPosition(game.getEnemyPos().x * tileSize, game.getEnemyPos().y * tileSize);
        window.draw(enermy_sprite);

        game.update(window);

        window.display();
    }
    return 0;
}