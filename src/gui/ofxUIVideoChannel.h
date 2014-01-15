/*
 * VideoChannel GUI
 */
#pragma once
#include "ofxUIWidgetWithLabel.h"

class ofxUIVideoChannel : public ofxUIWidgetWithLabel
{
public: ofxUIVideoChannel(float x, float y, float w, float h, ofTexture *_image, string _name) : ofxUIWidgetWithLabel()
    {
        rect = new ofxUIRectangle(x,y,w,h);
        init(w, h, _image, _name);
    }

    ofxUIVideoChannel(float x, float y, float w, float h, ofTexture *_image, string _name, bool _showLabel) : ofxUIWidgetWithLabel()
    {
        rect = new ofxUIRectangle(x,y,w,h);
        init(w, h, _image, _name);
        showLabel = _showLabel;
    }

    ofxUIVideoChannel(float w, float h, ofTexture *_image, string _name) : ofxUIWidgetWithLabel()
    {
        rect = new ofxUIRectangle(0,0,w,h);
        init(w, h, _image, _name);
    }

    ofxUIVideoChannel(float w, float h, ofTexture *_image, string _name, bool _showLabel) : ofxUIWidgetWithLabel()
    {
        rect = new ofxUIRectangle(0,0,w,h);
        init(w, h, _image, _name);
        showLabel = _showLabel;
    }

    void init(float w, float h, ofTexture *_image, string _name)
    {
		name = string(_name);
		kind = OFX_UI_WIDGET_IMAGE;
        showLabel = false;
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding);
		paddedRect->setParent(rect);

        draw_back = false;
        draw_fill = true;

		image = _image;

		label = new ofxUILabel(0,h+padding,(name+" LABEL"),name, OFX_UI_FONT_SMALL);
		label->setParent(label);
		label->setRectParent(rect);
        label->setEmbedded(true);

        cropImageToFitRect = true;
    }

    virtual void setDrawPadding(bool _draw_padded_rect)
	{
		draw_padded_rect = _draw_padded_rect;
        label->setDrawPadding(false);
	}

    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline)
	{
		draw_padded_rect_outline = _draw_padded_rect_outline;
        label->setDrawPaddingOutline(false);
	}

    virtual void drawFill()
    {
        if(draw_fill)
        {
			if(image != NULL)
			{
				ofxUIFill();
				ofxUISetColor(255);
                if(cropImageToFitRect)
                {
                    image->drawSubsection(rect->getX(), rect->getY(), rect->width, rect->height, 0, 0, rect->width, rect->height);
                }
                else
                {
                    image->draw(rect->getX(), rect->getY(), rect->width, rect->height);
                }
			}
        }
    }

    virtual void setVisible(bool _visible)
    {
        visible = _visible;
        label->setVisible(showLabel && _visible);
    }

    void setCropImageToFitRect(bool _cropImageToFitRect)
    {
        cropImageToFitRect = _cropImageToFitRect;
    }

	ofxUILabel *getLabel()
	{
		return label;
	}

    void setImage(ofTexture *_image)
    {
        image = _image;
    }

	virtual void setParent(ofxUIWidget *_parent)
	{
		parent = _parent;
        if(showLabel)
        {
            paddedRect->height += label->getPaddingRect()->height;
        }
        else
        {
            paddedRect->height += padding;
        }
        label->setVisible(showLabel);
	}

    virtual bool isDraggable()
    {
        return false;
    }


protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent;
	ofTexture *image;
    bool showLabel;
    bool cropImageToFitRect;
};

