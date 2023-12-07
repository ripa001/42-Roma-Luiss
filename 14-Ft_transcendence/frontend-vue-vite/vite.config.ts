import { fileURLToPath, URL } from 'node:url'

import vue from '@vitejs/plugin-vue'
import { defineConfig, loadEnv } from 'vite'
import { nodePolyfills } from 'vite-plugin-node-polyfills'

// https://vitejs.dev/config/
export default defineConfig(({command, mode}) => {
  const env = loadEnv(mode, process.cwd(), '');
  return {
    // base:  '/usr/share/nginx',
    server: {
      host: "0.0.0.0",
      fs: {
        strict: true,
        // allow: ['src', 'public', 'index.html', 'README.md', 'node_modules']
      },
      // hmr: {
      //   clientPort: 8080,
      // },
      port: Number(env.VITE_PORT_FRONT),
      watch: {
        usePolling: true,
      },
    },
    plugins: [
      nodePolyfills(),
      vue(),
    ],
    resolve: {
      alias: {
        '@': fileURLToPath(new URL('./src', import.meta.url))
      }
    },
    build: {
        rollupOptions: {
            output:{
                manualChunks(id) {
                    if (id.includes('node_modules')) {
                        return id.toString().split('node_modules/')[1].split('/')[0].toString();
                    }
                }
            }
        }
    }
  }
  }
);
