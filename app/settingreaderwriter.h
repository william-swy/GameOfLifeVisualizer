//
// Read and write contents for settings
//

#ifndef GAMEOFLIFEAPP_SETTINGREADERWRITER_H
#define GAMEOFLIFEAPP_SETTINGREADERWRITER_H

#include <exception>
#include <QColor>
#include <QFile>
#include <QTextStream>
#include <QDomDocument>

namespace Settings {
    static const QString file = ":/Data/Data/settings.xml";
    // class to serialize settings data
    class SettingData {
        QColor outlineColor;
        QColor aliveColor;
        QColor deadColor;
        int framerate;
        int width;
        int height;
    };

    class ReadException : public std::exception {
        const char* what() const throw() {
            return "Reading Settings File Exception";
        }
    };

    class WriteException : public std::exception {
        const char* what() const throw() {
            return "Writing Settings File Exception";
        }
    };

    static void write(SettingData& data) {
        QDomDocument document;
        QDomElement root = document.createElement("Setting");
        document.appendChild(root);

        QDomElement outline = document.createElement("Setting");
        outline.setAttribute("Outline", data.outlineColor.name());
        root.appendChild(outline);

        QDomElement alive = document.createElement("Setting");
        alive.setAttribute("Alive", data.aliveColor.name());
        root.appendChild(alive);

        QDomElement dead = document.createElement("Setting");
        dead.setAttribute("Dead", data.deadColor.name());
        root.appendChild(dead);

        QDomElement frame = document.createElement("Setting");
        frame.setAttribute("Frame", QString::number(data.framerate));
        root.appendChild(frame);

        QDomElement width = document.createElement("Setting");
        width.setAttribute("Width", QString::number(data.width));
        root.appendChild(width);

        QDomElement height = document.createElement("Setting");
        height.setAttribute("Height", QString::number(data.height));
        root.appendChild(height);

        QFile settings(file);
        if(!settings.open(QIODevice::WriteOnly | QIODevice::Text)) {
            throw WriteException;
        }
        else {
            QTextStream stream(&settings);
            stream << document.toString();
            settings.close();
        }
    }

    static SettingData* read() {
        QFile settings(file);
        if(!settings.open(QIODevice::ReadOnly | QIODevice::Text)) {
            throw ReadException;
        }
        else {
            QDomDocument document;
            if (!document.setContent(&settings)) {
                throw ReadException;
            }
            settings.close();

            QDomDocument root = document.firstChildElement();

        }
    }

}

#endif //GAMEOFLIFEAPP_SETTINGREADERWRITER_H
