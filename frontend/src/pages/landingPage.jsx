import React from 'react';
import { Link } from 'react-router-dom';
import topStars from '../assets/images/topstars.png';
import bottomAlien from '../assets/images/aliencut.png';
import cowufo from '../assets/images/cowufo.png';

export default function LandingPage() {
 

  return (
    <div
      className="relative flex flex-col items-center justify-center min-h-screen text-center px-4"
      style={{ backgroundColor: '#F8F3E7' }}
    >
      {/* ⭐ top */}
      <img
        src={topStars}
        alt="stars"
        className="w-full absolute top-0 left-0"
        style={{ margin: 0, padding: 0, zIndex: 0 }}
      />

      {/* 👽  */}
      <img
        src={bottomAlien}
        alt="alien"
        className="absolute bottom-0 right-0"
        style={{ width: '35%', zIndex: 0 }}
      />

      {/* 🐄  */}
      <div className="absolute bottom-24 left-4 z-10">
        <img
          src={cowufo}
          alt="cow UFO"
          className="w-100
           sm:w-80 md:w-96 lg:w-112 xl:w-128 2xl:w-144"
        />
      </div>

      {/*  Project credit text */}
      <div className="absolute bottom-4 left-4 z-10 text-left ">
        <p className="text-primaryBlue font-grover text-xl sm:text-2xl md:text-3xl leading-snug">
          A project by: <br />
          Isabel Hernandez, 
          Daniel Hernandez, <br/>
          and Cecilia Beringer
        </p>
      </div>

      {/* Main Content */}
      <div className="relative z-10 pb-20 max-w-4xl px-4">
        <h1 className="text-9xl font-grover text-primaryBlue mb-4">
          UFO Hunters
        </h1>
        <p className="text-3xl font-handlee text-gray-700 mb-6">
          Aliens Love Patterns—We Help You Catch Them!
        </p>

        <Link
          to="/predictions"
          className="font-grover text-primaryBlue text-4xl py-4 px-8 rounded-lg transition duration-200 border border-primaryBlue shadow-[3px_4px_8px_rgba(0,63,145,0.3)] bg-[#8AE37D] inline-block"
        >
          <div className="flex flex-col items-center leading-tight w-full">
            <span>Beam me to</span>
            <span className="underline">the Data!</span>
          </div>
        </Link>
      </div>
    </div>
  );
}
