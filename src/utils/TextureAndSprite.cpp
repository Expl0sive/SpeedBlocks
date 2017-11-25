#include "TextureAndSprite.h"

namespace tgui
{
    TextureAndSprite::TextureAndSprite(const Layout2d& size)
    {
        m_callback.widgetType = "TextureAndSprite";

        setSize(size);
    }

    TextureAndSprite::TextureAndSprite(const Layout& width, const Layout& height) :
        TextureAndSprite{Layout2d{width, height}}
    {
    }

    TextureAndSprite::TextureAndSprite(const TextureAndSprite& canvasToCopy) :
        ClickableWidget{canvasToCopy}
    {
        setSize(canvasToCopy.getSize());
    }

    TextureAndSprite& TextureAndSprite::operator= (const TextureAndSprite& right)
    {
        if (this != &right)
        {
            ClickableWidget::operator=(right);

            setSize(right.getSize());
        }

        return *this;
    }

    TextureAndSprite::Ptr TextureAndSprite::create(Layout2d size)
    {
        return std::make_shared<TextureAndSprite>(size);
    }

    TextureAndSprite::Ptr TextureAndSprite::copy(TextureAndSprite::ConstPtr canvas)
    {
        if (canvas)
            return std::static_pointer_cast<TextureAndSprite>(canvas->clone());
        else
            return nullptr;
    }

    void TextureAndSprite::setPosition(const Layout2d& position)
    {
        Widget::setPosition(position);

        m_sprite.setPosition(getPosition());
    }

    void TextureAndSprite::setSize(const Layout2d& size)
    {
        Widget::setSize(size);

        //m_sprite.setSize(getSize());
    }

    void TextureAndSprite::setOpacity(float opacity)
    {
        Widget::setOpacity(opacity);

        m_sprite.setColor({m_sprite.getColor().r, m_sprite.getColor().g, m_sprite.getColor().b, static_cast<sf::Uint8>(m_opacity * 255)});
    }

    void TextureAndSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_sprite, states);
    }
}