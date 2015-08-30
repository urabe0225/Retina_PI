// -*- C++ -*-
/*!
 * @file  Retina.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "Retina.h"
using namespace std;
using namespace cv;
// Module specification
// <rtc-template block="module_spec">
static const char* retina_spec[] =
  {
    "implementation_id", "Retina",
    "type_name",         "Retina",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "Kazuki Urabe",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.view", "0:parvo",
    "conf.default.log_sampling", "0:OFF",
    // Widget
    "conf.__widget__.view", "radio",
    "conf.__widget__.log_sampling", "radio",
    // Constraints
    "conf.__constraints__.view", "(1:magno,0:parvo)",
    "conf.__constraints__.log_sampling", "(1:ON,0:OFF)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Retina::Retina(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_inputIn("input", m_input),
    m_magnoOut("magno", m_magno),
    m_parvoOut("parvo", m_parvo)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Retina::~Retina()
{
}



RTC::ReturnCode_t Retina::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("input", m_inputIn);
  
  // Set OutPort buffer
  addOutPort("magno", m_magnoOut);
  addOutPort("parvo", m_parvoOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>
  bindParameter("view", m_view, "0:parvo");
  bindParameter("log_sampling", m_log_sampling, "0");
  // <rtc-template block="bind_config">
  // </rtc-template>
  inputFrame = cv::Mat::zeros(cv::Size(320,240),16);
  namedWindow( "retina", WINDOW_AUTOSIZE );
  cv::imshow( "retina", inputFrame);
  cv::waitKey(25);
  cout<<"Initialize OK"<<endl;
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Retina::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Retina::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Retina::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t Retina::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Retina::onDeactivated(RTC::UniqueId ec_id)
{
  inputFrame.release();
  outputFrame.release();
  parvoFrame.release();
  magnoFrame.release();
  fflg = false;
  retina->clearBuffers();
  while(m_inputIn.isNew()) m_inputIn.read();
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Retina::onExecute(RTC::UniqueId ec_id)
{
  if (!m_inputIn.isNew())
  { 
  return RTC::RTC_OK;
  }
  m_inputIn.read();

  m_input>>inputFrame;

  if(fflg == false) //一回目の初期化処理
  {
    if(m_log_sampling == 0)//OFF
      retina = cv::bioinspired::createRetina(inputFrame.size());
    else
      retina = cv::bioinspired::createRetina(inputFrame.size(), true, cv::bioinspired::RETINA_COLOR_BAYER, true, 2.0, 10.0);

    fflg = true;
  }
  retina->run(inputFrame);
  retina->getParvo(parvoFrame);
  retina->getMagno(magnoFrame);

  if(m_view == 0)
    cv::imshow("retina", parvoFrame);
  else
    cv::imshow("retina", magnoFrame);
  cv::waitKey(3);

  parvoFrame>>m_parvo;
  magnoFrame>>m_magno;
  m_parvoOut.write();
  m_magnoOut.write();

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Retina::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Retina::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Retina::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Retina::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Retina::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void RetinaInit(RTC::Manager* manager)
  {
    coil::Properties profile(retina_spec);
    manager->registerFactory(profile,
                             RTC::Create<Retina>,
                             RTC::Delete<Retina>);
  }
  
};


