#include "eco2dsolverui.h"
#include "ui_eco2dsolverui.h"

Eco2dSolverUI::Eco2dSolverUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Eco2dSolverUI)
{
    ui->setupUi(this);
    scene = nullptr;
    set_pens_brushes();
    solve_problem();
    rects = std::vector<QGraphicsRectItem*>();
    rects_label =  std::vector<QGraphicsTextItem *>();
    draw_state();
}

Eco2dSolverUI::~Eco2dSolverUI()
{
    delete ui;
}

void Eco2dSolverUI::solve_problem()
{

    r.set_eco_connection(&es);
    r.load_eco_data("C://Users//user//Documents//Alexandre//C++//IA//ECO_2D_SOLVER//input.txt");
    es.find_solution();
    o.set_eco_connection(&es);
    o.print_eco_data("C://Users//user//Documents//Alexandre//C++//IA//ECO_2D_SOLVER//output.txt");
    it_current_state = es.l_states.begin();
    current_state_number = 1;
    max_state_number = es.l_states.size();
    draw_state();
}

void Eco2dSolverUI::draw_state()
{
    if(scene == nullptr)
    {
         scene = new QGraphicsScene(this);
    }else
    {
        delete scene;
        ui->gvCurrentState->items().clear();
        scene = new QGraphicsScene(this);
    }
    rects = std::vector<QGraphicsRectItem*>();
    rects_label =  std::vector<QGraphicsTextItem *>();
    ui->gvCurrentState->setScene(scene);
    std::string state_percentage = std::to_string(current_state_number) + "/" + std::to_string(max_state_number);
    ui->lb_current_state->setText(state_percentage.c_str());

    draw_container();
    draw_rectangle();


}

void Eco2dSolverUI::draw_rectangle()
{

    for(size_t i = 0; i < it_current_state->v_rects.size() ; i++)
    {



        if(it_current_state->v_rects[i].damaged){
        rects.push_back(scene->addRect(scale_factor* it_current_state->v_rects[i].current_coords.x,
                                       scale_factor*(-it_current_state->v_rects[i].current_coords.y),
                                       scale_factor*it_current_state->v_rects[i].current_coords.l,
                                       scale_factor*(- it_current_state->v_rects[i].current_coords.w),
                                       *black_pen,
                                       colors[1]));
        }else
        {
            rects.push_back(scene->addRect(scale_factor* it_current_state->v_rects[i].current_coords.x,
                                           scale_factor*(-it_current_state->v_rects[i].current_coords.y),
                                           scale_factor*it_current_state->v_rects[i].current_coords.l,
                                           scale_factor*(- it_current_state->v_rects[i].current_coords.w),
                                           *black_pen,
                                           colors[0]));
        }
        int x_label = scale_factor* it_current_state->v_rects[i].current_coords.x +
                      (scale_factor* it_current_state->v_rects[i].current_coords.l/2) - 5;
        int y_label = scale_factor*(-it_current_state->v_rects[i].current_coords.y) -
                      (scale_factor* it_current_state->v_rects[i].current_coords.w);
        rects_label.push_back(scene->addText(std::to_string(i).c_str()));
        rects_label[rects_label.size()-1]->setPos(x_label,y_label);

        if(it_current_state->rect_action == i)
        {
            rects_label[rects_label.size()-1]->setDefaultTextColor(Qt::darkRed);
        }else
        {
            rects_label[rects_label.size()-1]->setDefaultTextColor(Qt::white);
        }



    }
}

void Eco2dSolverUI::draw_container()
{

    rects.push_back(scene->addRect(scale_factor*es.container_x,scale_factor*(-es.container_y)
                                   ,scale_factor*es.container_l,
                                   scale_factor*(-es.container_w),*black_pen));
}

void Eco2dSolverUI::set_pens_brushes()
{
    red_brush = new QBrush(Qt::red);
    black_pen = new QPen(Qt::black);
    red_pen = new QPen(Qt::red);
    red_brush = new QBrush(Qt::red);
    blue_brush = new QBrush(Qt::blue);
    black_pen->setWidth(2);
    red_pen->setWidth(2);
}

void Eco2dSolverUI::on_left_clicked()
{
    if(current_state_number != 1)
    {
        current_state_number--;
        it_current_state--;
    }
    draw_state();
}

void Eco2dSolverUI::on_pushButton_clicked()
{
    if(current_state_number < max_state_number)
    {
        current_state_number++;
        it_current_state++;
    }
    draw_state();
}

void Eco2dSolverUI::on_pushButton_2_clicked()
{

    while(current_state_number < max_state_number)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        on_pushButton_clicked();
     }
}
