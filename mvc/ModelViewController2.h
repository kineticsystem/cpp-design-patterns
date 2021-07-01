#ifndef MODEL_VIEW_CONTROLLER_2_H
#define MODEL_VIEW_CONTROLLER_2_H

#include <iostream>
#include <sstream>
#include <QString>
#include <memory>

/* ////////////////////////////////////////////////////////////////////////////
 * MOVEL-VIEW-CONTROLLER PATTERN WITH GLOBAL MODELS
 * This is a MVC implementation using shared smart pointers.
 */

namespace ModelViewController2 {

    /* /////////////////////////////////////////////////////////////////////////
     * Model.
     */

    class Model
    {
    public:
        Model() {}

        QString name() const  {
            return m_name;
        }

        void setName(const QString &name) {
            m_name = name;
        }

        std::string toString() const {
            std::ostringstream buffer;
            buffer << "Model[name=" << m_name.toStdString() << "]";
            return buffer.str();
        }

    private:
        QString m_name;
    };

    /* /////////////////////////////////////////////////////////////////////////
     * View.
     */

    // The model associated to the View is never null. If no model is given,
    // a default model is used.
    class View
    {

    public:

        View() {}

        QString nameField() const {
            return m_model->name();        // No need to check for null.
        }

        void setNameField(const QString &name) {
            return m_model->setName(name); // No need to check for null.
        }

        void setModel(std::shared_ptr<Model> model) {
            m_model = model;
        }

    private:

        std::shared_ptr<Model> m_model = std::make_unique<Model>();
    };

    /* /////////////////////////////////////////////////////////////////////////
     * Examples.
     */
    struct Test {
        static void execute() {

            std::cout << "MODEL-VIEW-CONTROLLER-2" << std::endl;

            View view1;
            View view2;

            std::cout << "Updating default model for View1 and View2" << std::endl;

            view1.setNameField("Fred");
            view2.setNameField("Tony");

            std::cout << view1.nameField().toStdString() << std::endl;
            std::cout << view2.nameField().toStdString() << std::endl;

            std::cout << "Changing View2 model" << std::endl;

            std::shared_ptr<Model> model = std::make_shared<Model>();
            model->setName("John");
            view2.setModel(model);

            std::cout << view1.nameField().toStdString() << std::endl;
            std::cout << view2.nameField().toStdString() << std::endl;

            std::cout << "Resetting View2 model" << std::endl;

            view2.setModel(std::make_shared<Model>());
            std::cout << view1.nameField().toStdString() << std::endl;
            std::cout << view2.nameField().toStdString() << std::endl;

            std::cout << std::endl;
        }
    };
}

#endif // MODEL_VIEW_CONTROLLER_2_H
