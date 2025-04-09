import { Routes, Route } from 'react-router-dom';
import LandingPage from './pages/landingPage.jsx'
import PredictionsPage from './pages/predictionsPage.jsx';

export default function App() {
  return (
    <Routes>
      <Route path="/" element={<LandingPage/>} />
      <Route path="/predictions" element={<PredictionsPage />} />
    </Routes>
  );
}