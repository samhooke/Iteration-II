#include "Content.hpp"
#include "Defs.hpp"
#include "GameEngine.hpp"
#include "states/SceneState.hpp"
#include "states/PlayState.hpp"
#include "states/TitleState.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "General.hpp"

Content::Content(GameEngine* game) {
    this->game = game;
    Reset();
}

void Content::Reset() {
    contentPosition = 0;
}

void Content::LoadOutline() {

    // Read the file outline.txt and generate the content list (of levels and scenes)

    bool failure = false;

    std::string line;
    std::ifstream myfile(OUTLINE_FILENAME);
    if (myfile.is_open()) {
        while (getline(myfile, line) && !failure) {
            std::vector<std::string> lineExp = ::Explode(line, ' ');
            if (lineExp.size() == 2) {
                // Read the tile and filename
                ContentItem ci;
                if (lineExp[0] == "Scene:") {
                    ci.type = ContentType::Scene;
                } else if (lineExp[0] == "Level:") {
                    ci.type = ContentType::Level;
                } else {
                    failure = true;
                    std::cout << "ERROR: Unknown content type '" << lineExp[0] << "'" << std::endl;
                }

                if (!failure) {
                    ci.filename = lineExp[1];
                    AddContent(ci);
                }
            } else {
                failure = true;
                std::cout << "ERROR: Invalid content item or filename contains spaces" << std::endl;
            }
        }
    } else {
        std::cout << "ERROR: Could not open outline file" << std::endl;
    }
}

void Content::Next() {
    contentPosition++;
}

void Content::Load() {
#ifdef DEBUG_VERBOSE
    std::cout << "Going to load new content" << std::endl;
#endif // DEBUG_VERBOSE
    if (AtValidContent()) {
        ContentType type = GetCurrentContentType();

        if (type == ContentType::Level) {
#ifdef DEBUG_VERBOSE
            std::cout << "game->ChangeState(PlayState::Instance());" << std::endl;
#endif // DEBUG_VERBOSE
            // Load level
            game->ChangeState(PlayState::Instance());
        }
        if (type == ContentType::Scene) {
#ifdef DEBUG_VERBOSE
            std::cout << "game->ChangeState(SceneState::Instance());" << std::endl;
#endif // DEBUG_VERBOSE
            // Load scene
            game->ChangeState(SceneState::Instance());
        }
    } else {
        std::cout << "ERROR: Exceeded content range" << std::endl;
        game->ChangeState(TitleState::Instance());
    }
}

bool Content::AtValidContent() {
    return contentPosition < (int)contentList.size();
}

void Content::AddContent(ContentItem content) {
    contentList.push_back(content);
}

ContentType Content::GetCurrentContentType() {
    if (AtValidContent()) {
        return contentList[contentPosition].type;
    } else {
        std::cout << "WARNING: ContentType type out of range" << std::endl;
        return ContentType::Level;
    }
}

std::string Content::GetCurrentContentFilename() {
    if (AtValidContent()) {
        std::ostringstream os;
        if (contentList[contentPosition].type == ContentType::Level)
            os << LEVEL_DIR;
        if (contentList[contentPosition].type == ContentType::Scene)
            os << SCENE_DIR;
        os << contentList[contentPosition].filename;
        return os.str();
    } else {
        std::cout << "WARNING: ContentType filename out of range" << std::endl;
        return "";
    }
}
