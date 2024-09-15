#include "ble_rimu.h"
#include "ble_srv_common.h"
#include "sdk_common.h"

static void on_connect(ble_rimu_t * p_rimu, ble_evt_t * p_ble_evt)
{
    p_rimu->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
}

static void thread_entry_fn_fifo(void *p1, void *p2, void *p3)
{
        struct fifo_item_t  *rx_data;
        uint32_t i;

        /* Get items from fifo */
        for (i = 0U; i < LIST_LEN; i++) {
                rx_data = k_fifo_get((struct k_fifo *)p1, K_NO_WAIT);
                zassert_equal(rx_data->value, fifo_data[i].value);
        }

        /* Put items into fifo */
        for (i = 0U; i < LIST_LEN; i++) {
                fifo_data[i].value *= i;
                k_fifo_put((struct k_fifo *)p1, &fifo_data[i]);
        }

        /* Give control back to Thread A */
        k_sem_give(&sema);
}
void ble_rimu_on_ble_evt(ble_rimu_t * p_rimu, ble_evt_t * p_ble_evt)
{
    if ((p_rimu == NULL) || (p_ble_evt == NULL))
    {
        return;
    }

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            on_connect(p_rimu, p_ble_evt);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnect(p_rimu, p_ble_evt);
            break;

        case BLE_GATTS_EVT_WRITE:
            on_write(p_rimu, p_ble_evt);
            break;

        case BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST:
            on_authorize_req(p_rimu, p_ble_evt);
            break;

        default:
            // No implementation needed.
            break;
    }
}