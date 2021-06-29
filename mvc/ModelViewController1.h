#ifndef MODEL_VIEW_CONTROLLER_1_H
#define MODEL_VIEW_CONTROLLER_1_H

#include <iostream>
#include <sstream>
#include <QString>

/* ////////////////////////////////////////////////////////////////////////////
 * MOVEL-VIEW-CONTROLLER PATTERN WITH GLOBAL MODELS
 * This is a MVC implementation using a static empty model to avoid checking
 * for null models.
 */

namespace ModelViewController1 {

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
    // a temporary global model is associated to all Views to avoid checking
    // for nullptr.
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

        void setModel(Model *model) {
            if (model) {
                m_model = model;
            } else {
                m_model =  View::staticEmptyModel();
            }
        }

    private:

        static Model *staticEmptyModel() {
            static Model model;
            return &model;
        }

        Model *m_model = View::staticEmptyModel();
    };

    /* /////////////////////////////////////////////////////////////////////////
     * Examples.
     */
    struct Test {
        static void execute() {

            std::cout << "MODEL-VIEW-CONTROLLER-1" << std::endl;

            View view1;
            View view2;

            std::cout << "Updating global model for View1 and View2" << std::endl;

            view1.setNameField("Fred");

            std::cout << view1.nameField().toStdString() << std::endl;
            std::cout << view2.nameField().toStdString() << std::endl;

            std::cout << "Changing View2 model" << std::endl;

            std::unique_ptr<Model> model = std::make_unique<Model>();
            model->setName("John");
            view2.setModel(model.get());

            std::cout << view1.nameField().toStdString() << std::endl;
            std::cout << view2.nameField().toStdString() << std::endl;

            std::cout << "Resetting View2 to global model" << std::endl;

            view2.setModel(nullptr);
            std::cout << view1.nameField().toStdString() << std::endl;
            std::cout << view2.nameField().toStdString() << std::endl;

            std::cout << std::endl;
        }
    };
}

#endif // MODEL_VIEW_CONTROLLER_1_H
