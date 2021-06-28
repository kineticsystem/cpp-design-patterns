#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <sstream>
#include <QString>
#include <memory>

namespace MVC {

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

        QString surname() const {
            return m_surname;
        }

        void setSurname(const QString &surname) {
            m_surname = surname;
        }

        std::string toString() const {
            std::ostringstream buffer;
            buffer << "Model[name=" << m_name.toStdString()
                   << ",surname=" << m_surname.toStdString()
                   << "]";
            return buffer.str();
        }

    private:
        QString m_name;
        QString m_surname;
    };

    /* /////////////////////////////////////////////////////////////////////////
     * View.
     */

    class View
    {
    public:
        View() {
            // This is a static empty model used to simplify the GUI
            // construction.
            static Model model;
            m_model = &model;
        }

        Model * model() {
            return m_model;
        }

        void setModel(Model *model) {
            m_model = model;
        }
    private:
        Model *m_model = nullptr;
    };

    /* /////////////////////////////////////////////////////////////////////////
     * Examples.
     */
    struct Test {
        static void execute() {

            std::cout << "MVC" << std::endl;

            View view1;
            view1.model()->setName("FirstName");
            view1.model()->setSurname("Surname");

            View view2;

            std::cout << view1.model()->toString() << std::endl;
            std::cout << view2.model()->toString() << std::endl;

            std::unique_ptr<Model> model = std::make_unique<Model>();
            model->setName("John");
            model->setSurname("Doe");
            view2.setModel(model.get());

            std::cout << view1.model()->toString() << std::endl;
            std::cout << view2.model()->toString() << std::endl;

            std::cout << std::endl;
        }
    };
}

// QTableView::setModel(new QTableModel(0, 0, this));
#endif // VIEW_H
