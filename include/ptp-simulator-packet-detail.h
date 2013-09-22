#ifndef __PTP_SIMULATOR_PACKET_DETAIL_H__
#define __PTP_SIMULATOR_PACKET_DETAIL_H__

#include <gtk/gtk.h>

typedef struct _PtpSimulatorPacketDetail            PtpSimulatorPacketDetail;
typedef struct _PtpSimulatorPacketDetailClass       PtpSimulatorPacketDetailClass;

#define PTP_SIMULATOR_TYPE_PACKET_DETAIL            (ptp_simulator_packet_detail_get_type())
#define PTP_SIMULATOR_PACKET_DETAIL(obj)            (G_TYPE_CHECK_INSTANCE_CAST((obj), PTP_SIMULATOR_TYPE_PACKET_DETAIL, PtpSimulatorPacketDetail))
#define PTP_SIMULATOR_IS_PACKET_DETAIL(obj)         (G_TYPE_CHECK_INSTANCE_TYPE((obj), PTP_SIMULATOR_TYPE_PACKET_DETAIL))
#define PTP_SIMULATOR_PACKET_DETAIL_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST((klass),  PTP_SIMULATOR_TYPE_PACKET_DETAIL, PtpSimulatorPacketDetailClass))
#define PTP_SIMULATOR_IS_PACKET_DETAIL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass),  PTP_SIMULATOR_TYPE_PACKET_DETAIL))
#define PTP_SIMULATOR_PACKET_DETAIL_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS((obj),  PTP_SIMULATOR_TYPE_PACKET_DETAIL, PtpSimulatorPacketDetailClass))

struct _PtpSimulatorPacketDetail {
    GtkGrid                 parent_instance;
    
    GtkToolItem             *item_new;
};

struct _PtpSimulatorPacketDetailClass {
    GtkGridClass            parent_class;
};

GtkWidget *ptp_simulator_packet_detail_new(void);

#endif

