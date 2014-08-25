#ifndef LANDINGGEARCONTROLLER_H
#define LANDINGGEARCONTROLLER_H
#include "../../controller.h"
#include "landinggearmodel.h"
#include "../../../processor.h"
#include <boost/signals2.hpp>
#include "../../../namespaces.h"

namespace PPLNAMESPACE {

class LandingGearController : public Controller < LandingGearModel >, private PPL::Processor
{
public:
    LandingGearController(LandingGearModel& model);
    
    virtual ~LandingGearController();
    
    virtual float callback(float, float, int);
    
    /**
     * @brief Starts the landing gear deployment process
     */
    void deploy();
    /**
     * @brief Starts the landing gear retraction process
     */
    void retract();
    
    typedef boost::signals2::signal<void ()> signal_type;
    
    typedef signal_type::slot_type listener_type;
    
    boost::signals2::connection addExtendFinishedListener(const listener_type& listener);
    boost::signals2::connection addRetractFinishedListener(const listener_type& listener);
    boost::signals2::connection addExtendStartedListener(const listener_type& listener);
    boost::signals2::connection addRetractStartedListener(const listener_type& listener);
    
private:
    float lastDeployRatio;
    
    /**
     * @brief A signal emitted when the landing gear has finished extending
     */
    signal_type extendedSignal;
    /**
     * @brief A signal emitted when the landing gear has finished retracting
     */
    signal_type retractedSignal;
    /**
     * @brief A signal emitted when the landing gear has started extending
     */
    signal_type extensionStartedSignal;
    /**
     * @brief A signal emitted when the landing gear has started retracting
     */
    signal_type retractionStartedSignal;
    
    static bool isBasicallyZero(float value);
    static bool isBasicallyOne(float value);
};

}
#endif // LANDINGGEARCONTROLLER_H
