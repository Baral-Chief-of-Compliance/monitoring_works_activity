<template>
    <v-container>
        <v-row>
            <div class="text-h5">Infomation about connection <span class="font-weight-bold">{{ this.connection_inf.ip }}:{{ this.connection_inf.port }}</span> </div>

            <!-- <v-card color="green" class="ml-5 text-center" width="100" height="25">
                    Online
            </v-card> -->
        </v-row>
       
        <v-btn color="teal" @click="back_index_page" class="mt-4">
            On index page
        </v-btn>



        <v-row class="pa-3 mt-4">
            last date seen: <span class="font-weight-bold">{{ this.connection_inf.date }}</span>
        </v-row>

        <v-row class="pa-3">
            last time seen: <span class="font-weight-bold">{{ this.connection_inf.time }}</span>
        </v-row>

        <v-row class="pa-3">
            login: <span class="font-weight-bold">{{ this.connection_inf.login }}</span>
        </v-row>
            
        <v-row class="pa-3">
            user: <span class="font-weight-bold">{{ this.connection_inf.name }}</span>
        </v-row>

        <v-row class="pa-3">
            domain: <span class="font-weight-bold">{{ this.connection_inf.domain }}</span>
        </v-row>

        <v-btn
            @click="get_screenshot()"
            class="mt-5"
            color="indigo"
            block
        >
            get screenshot
        </v-btn>

        {{ this.screenshot }}
    </v-container>
    <!-- {{ this.format_date(this.connection_inf.time, this.connection_inf.date) }}
    {{ this.get_time_now }} -->
</template>

<script>
import axios from 'axios';
import moment from 'moment';


export default{
    data(){
        return{
            connection_inf: {
                login: null,
                ip: null,
                port: null,
                name: null,
                domain: null,
                date: null,
                time: null
            },
            screenshot: ""
        }
    },

    computed: {
        get_time_now(){
            return moment().format('DD MM YYYY hh:mm:ss')
        }
    },

    methods:{
        get_inf_connection(){
            axios.get(
                `http://127.0.0.1:5000/all_conections/${this.$route.params.ip_port}`
            ).then(
                response => (
                    this.connection_inf = response.data
                )
            )
        },

        back_index_page(){
            this.$router.push({name: 'Home'})
        },

        format_date(time, date){
            return moment(`${date} ${time}`, "DD MM YYYY hh:mm:ss");
        },

        get_screenshot(){
            axios.get(
                `http://127.0.0.1:5000/all_connections/${this.$route.params.ip_port}/get_screenshot`
            ).then(
                response =>(
                    this.screenshot = response.data
                )
            )
        }
    },

    mounted(){
        this.get_inf_connection()
    }
}
</script>