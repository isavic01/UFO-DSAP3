import React, { useState } from 'react';
import { Link } from 'react-router-dom';
import topStars from '../assets/images/topstars.png';
import bottomAlien from '../assets/images/aliencut.png';
import cowufo from '../assets/images/cowufo.png';
import universe from '../assets/images/universe.png';
import alien from '../assets/images/alienfullbody.png';

export default function PredictionsPage() {
  const [isRotating, setIsRotating] = useState(false);

  const handleYearChange = (e) => {
    // Trigger rotation when a new year is selected
    setIsRotating(true);
    setTimeout(() => {
      setIsRotating(false);
    }, 1000); // Duration of rotation in ms
  };

  return (
    <div className="min-h-screen bg-[#F8F3E7] p-8">
      {/* Centered heading container */}
      <div className="flex justify-center relative">
        <h1 className="text-7xl font-bold font-grover text-primaryBlue">
          UFO Predictions
        </h1>
        {/* Universe image is absolutely positioned so it doesn't shift the text */}
        <img
          src={universe}
          alt="universe"
          className={`absolute origin-center right-[40px] top-0 ${isRotating ? "animate-spin" : ""}`}
          style={{ width: '250px' }}
        />
      </div>
      
      {/* Row for alien, 'Select year' text, and dropdown */}
      <div className="-mt-14 pl-0 pr-0 flex items-center">
        {/* Alien image placed before the text */}
        <img 
          src={alien} 
          alt="alien full body" 
          className="w-36 mr-4" 
        />
        <p className="font-grover text-black text-left text-5xl mr-4">
          Select year
        </p>
        <select
          onChange={handleYearChange}
          className="p-2 text-3xl font-grover border border-gray-300 rounded bg-[#8EB071]"
        >
          <option value="2025">2025</option>
          <option value="2024">2024</option>
          <option value="2023">2023</option>
          <option value="2022">2022</option>
        </select>
      </div>
    </div>
  );
}
