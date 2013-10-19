#include "Content.hpp"
#include "Defs.hpp"
#include "GameEngine.hpp"
#include "states/SceneState.hpp"
#include "states/PlayState.hpp"
#include "states/TitleState.hpp"

Content::Content(GameEngine* game) {
    this->game = game;
    Reset();
}

void Content::Reset() {
    contentPosition = 0;
}

void Content::LoadOutline() {
    // Load the level list
    ContentItem a;
    a.type = ContentType::Scene;
    a.filename = "000.txt";

    ContentItem b;
    b.type = ContentType::Level;
    b.filename = "000.txt";

    AddContent(a);
    AddContent(b);
}

void Content::Next() {
    contentPosition++;
}

void Content::Load() {
    if (AtValidContent()) {
        ContentType type = GetCurrentContentType();

        if (type == ContentType::Level) {
            // Load level
            game->ChangeState(PlayState::Instance());
        }
        if (type == ContentType::Scene) {
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
