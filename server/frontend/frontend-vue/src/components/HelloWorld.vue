<template>
  <v-container>
    <div class="text-h5">list of connections</div>
    <v-btn @click="get_list_conections" block class="my-5" color="teal">Update list of connections</v-btn>

    <div v-for="connect in list_connections">
      <v-hover>
        <template v-slot:default="{ isHovering, props }">
          <v-card 
            class="pa-5 my-4"
            v-bind="props"
            :color="isHovering ? 'indigo' : undefined"
            :to="{ name: 'infConnection', params: {ip_port: connect.path}}"
          
          >
            <v-row>
              <v-col>
                login: <span class="font-weight-bold">{{ connect.login }}</span>
              </v-col>
              <v-col>
                ip: <span class="font-weight-bold">{{ connect.ip }}</span>
              </v-col>
              <v-col>
                port: <span class="font-weight-bold">{{ connect.port }}</span>
              </v-col>
              <v-col>
                user: <span class="font-weight-bold">{{ connect.name }}</span>
              </v-col>
              <v-col>
                domain: <span class="font-weight-bold">{{ connect.domain }}</span>
              </v-col>
              <v-col>
                last date: <span class="font-weight-bold">{{ connect.date }}</span>
              </v-col>
              <v-col >
                last time: <span class="font-weight-bold">{{ connect.time }}</span>
              </v-col>
            </v-row>
          </v-card>
      </template>
    </v-hover>
    </div>
  </v-container>
</template>

<script>
import axios from 'axios';

export default{
  data(){
    return{
      list_connections: []
    }
  },
  methods:{
    get_list_conections(){
      axios.get("http://127.0.0.1:5000/all_conections").then(
        response => (
          this.list_connections = response.data.connections
        )
      )
    }
  },

  mounted(){
    this.get_list_conections()
  }
}
</script>