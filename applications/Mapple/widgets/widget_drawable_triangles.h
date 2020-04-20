#ifndef WIDGET_DRAWABLE_TRIANGLES_H
#define WIDGET_DRAWABLE_TRIANGLES_H

#include <QWidget>

#include "widgets/widget_drawable.h"

namespace Ui {
    class WidgetTrianglesDrawable;
}

namespace easy3d {
    class Model;
    class TrianglesDrawable;
}


class WidgetTrianglesDrawable : public WidgetDrawable {
Q_OBJECT

public:
    explicit WidgetTrianglesDrawable(QWidget *parent);

    ~WidgetTrianglesDrawable() override;

    // update the panel to be consistent with the drawable's rendering parameters
    void updatePanel() override;

    // update the OpenGL buffers
    virtual void updateRendering() override;

    easy3d::TrianglesDrawable *drawable();

public slots:

    void setDrawableVisible(bool);
    void setActiveDrawable(const QString &);

    void setPhongShading(bool);
    void setLighting(const QString &);

    void setColorScheme(const QString &);
    void setDefaultColor();
    void setDistinctBackColor(bool);

    void setBackColor();
    void setTextureFile();

    void setTextureRepeat(int);
    void setTextureFractionalRepeat(int);

    void setHighlight(bool);
    void setHighlightMin(int);
    void setHighlightMax(int);

    void setOpacity(int);

    void setScalarFieldStyle(int);
    void setScalarFieldClamp(bool);
    void setScalarFieldClampLower(double);
    void setScalarFieldClampUpper(double);

    void setVectorField(const QString &);
    void setVectorFieldScale(double);

private:
    void connectAll();
    void disconnectAll();

    void disableUnavailableOptions();

    void updateVectorFieldBuffer(easy3d::Model *model, const std::string &name);

    // model depended stuff
    std::vector<std::string> vectorFields(const easy3d::Model *model);

private:
    Ui::WidgetTrianglesDrawable *ui;

private:
    // the state of the rendering panel
    struct State {
        State() : initialized(false), coloring("uniform color"), scalar_style(0), clamp_value(true),
                  clamp_value_lower(5.0), clamp_value_upper(5.0), vector_field("disabled"), vector_field_scale(1.0) {
        }

        bool initialized;
        std::string coloring;
        int scalar_style;
        bool clamp_value;
        double clamp_value_lower;
        double clamp_value_upper;
        std::string vector_field;
        double vector_field_scale;
    };

    std::unordered_map<easy3d::TrianglesDrawable *, State> states_;
};

#endif // WIDGET_DRAWABLE_TRIANGLES_H
