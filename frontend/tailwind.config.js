/** @type {import('tailwindcss').Config} */
export default {
    content: [
      "./index.html",
      "./src/**/*.{js,ts,jsx,tsx}",
    ],
    theme: {
      extend: {
        fontFamily: {
            grover: ['"Irish Grover"', 'system-ui'],
            delius: ['"Delius"', 'cursive'],
            handlee: ['"Handlee"', 'cursive']
          },
        colors: {
            primaryBlue: '#003F91',
            backgroundCream: '#F8F3E7'
        }
      },
    },
    plugins: [],
  }

  