import React from 'react';
import { Link } from 'react-router-dom';

export default function LandingPage() {
  console.log('✅ LandingPage component loaded');

  return (
    <div className="flex flex-col items-center justify-center min-h-screen bg-gray-100 text-center px-4">
      <h1 className="text-4xl font-bold text-indigo-700 mb-4">
        Welcome to the UFO Tracker 🌌
      </h1>
      <p className="text-lg text-gray-700 mb-6">
        Explore sightings, data, and predictions from across the universe.
      </p>

      <Link
        to="/predictions"
        className="bg-indigo-600 hover:bg-indigo-700 text-white font-semibold py-2 px-6 rounded-lg transition duration-200"
      >
        Go to Predictions
      </Link>
    </div>
  );
}
