#include "Content.hpp"
#include "Defs.hpp"
#include "GameEngine.hpp"
#include "states/SceneState.hpp"
#include "states/PlayState.hpp"

Content::Content(GameEngine* game) {
    this->game = game;
}

void Content::LoadOutline() {
    // Load the level list
    ContentItem a;
    a.type = ContentType::Level;
    a.filename = "001.txt";
    AddContent(a);
}

void Content::LoadNext() {
    contentPosition++;
    ContentType type = GetCurrentContentType();

    if (type == ContentType::Level) {
        // Load level
        game->ChangeState(PlayState::Instance());
    }
    if (type == ContentType::Scene) {
        // Load scene
        game->ChangeState(SceneState::Instance());
    }
}

void Content::AddContent(ContentItem content) {
    contentList.push_back(content);
}

ContentType Content::GetCurrentContentType() {
    if (contentPosition < (int)contentList.size()) {
        return contentList[contentPosition].type;
    } else {
        std::cout << "WARNING: ContentType type out of range" << std::endl;
        return ContentType::Level;
    }
}

std::string Content::GetCurrentContentFilename() {
    if (contentPosition < (int)contentList.size()) {
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
